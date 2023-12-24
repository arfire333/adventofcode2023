#include <libaoc.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using pulse_t = pair<string, bool>;
using pulse_pair_t = pair<string, pulse_t>;
using pulse_queue_t = queue<pulse_pair_t>;

class pulse_module {
  static pulse_queue_t pulse_queue_;
  static int64_t low_pulse_count_;
  static int64_t high_pulse_count_;
  static int64_t button_presses_;

  string name_;
  map<string, pulse_t, less<>> inputs_;
  vector<string> outputs_;
  bool state_ = false;
  int64_t first_low_ = -1;

 protected:
  void set(bool s) { state_ = s; }
  map<string, pulse_t, less<>>& inputs() { return inputs_; }
  void toggle() { state_ = !state_; }
  void set_first_low() { first_low_ = button_presses_; };
  void send() {
    for (const auto& out : outputs_) {
      if (state_) {
        high_pulse_count_++;
      } else {
        low_pulse_count_++;
      }

      pulse_queue_.emplace(out, pulse_t(name_, state_));
    }
  }

  virtual void process(map<string, unique_ptr<pulse_module>, less<>>& modules,
                       const pulse_t& in) = 0;
  string name() const { return name_; };

 public:
  virtual ~pulse_module() = default;
  void add_input(const string& input_name, bool initial_state = false) {
    inputs_[input_name] = pulse_t(input_name, initial_state);
  }
  int64_t button_presses() const { return button_presses_; }
  int64_t first_low() const { return first_low_; }
  void set_name(const string_view& in) { name_ = in; }
  void set_outputs(const vector<string>& outputs) { outputs_ = outputs; }

  static int64_t pulse_product() {
    return low_pulse_count_ * high_pulse_count_;
  }
  static void push_button(
      map<string, unique_ptr<pulse_module>, less<>>& modules) {
    low_pulse_count_++;
    button_presses_++;

    modules["broadcaster"]->process(modules, pulse_t("button", false));

    while (!pulse_queue_.empty()) {
      const auto& [name, pulse] = pulse_queue_.front();
      pulse_queue_.pop();
      modules.at(name)->process(modules, pulse);
    }
  }
};

pulse_queue_t pulse_module::pulse_queue_;
int64_t pulse_module::low_pulse_count_ = 0;
int64_t pulse_module::high_pulse_count_ = 0;
int64_t pulse_module::button_presses_ = 0;

class flip_flop final : public pulse_module {
  void process(map<string, unique_ptr<pulse_module>, less<>>& modules,
               const pulse_t& in) override {
    if (in.second) {
      return;
    }
    toggle();
    send();
  }
};

class conjunct final : public pulse_module {
  void process(map<string, unique_ptr<pulse_module>, less<>>& modules,
               const pulse_t& in) override {
    inputs().at(in.first) = in;
    bool all_high = true;
    for (const auto& [from, pulse] : inputs()) {
      if (!pulse.second) {
        all_high = false;
        break;
      }
    }
    if (all_high) {
      set(false);
    } else {
      if ((name().compare("qt") == 0 || name().compare("qb") == 0 ||
           name().compare("mp") == 0 || name().compare("ng") == 0) &&
          first_low() < 0) {
        set_first_low();
      }
      set(true);
    }

    send();
  }
};

class broadcaster final : public pulse_module {
 public:
  void process(map<string, unique_ptr<pulse_module>, less<>>& modules,
               const pulse_t& in) override {
    pulse_module::set(false);
    pulse_module::send();
  }
};

class output_module final : public pulse_module {
 public:
  void process(map<string, unique_ptr<pulse_module>, less<>>& modules,
               const pulse_t& in) override {
    if (in.second == false) {
      cout << "Module: " << name() << " received low pulse after "
           << button_presses() << " presses.\n";
    }

    pulse_module::set(false);
    pulse_module::send();
  }
};

void getData(istream& in,
             map<string, unique_ptr<pulse_module>, less<>>& modules) {
  string s;
  map<string, vector<string>, less<>> sources;
  while (getline(in, s) && s.size()) {
    cout << s << "\n";
    size_t start = 0;
    auto stop = s.find_first_of(" ");
    string name = s.substr(start, stop);
    char type = name[0];
    if (name[0] != 'b') {
      name = name.substr(1);
    }
    start = stop + 4;
    vector<string> outputs;
    while (stop != string::npos) {
      stop = s.find_first_of(",", start);
      string output = s.substr(start, stop - start);
      outputs.emplace_back(output);
      sources[output].emplace_back(name);
      start = stop + 2;
    }
    switch (type) {
      case 'b':
        modules[name] = make_unique<broadcaster>();
        break;
      case '%':
        modules[name] = make_unique<flip_flop>();
        break;
      case '&':
        modules[name] = make_unique<conjunct>();
        break;
      default:
        break;
    }
    modules[name]->set_outputs(outputs);
    modules[name]->set_name(name);
  }
  for (const auto& [output, source_list] : sources) {
    for (const auto& source : source_list) {
      if (modules.find(output) == modules.end()) {
        modules[output] = make_unique<output_module>();
      }
      modules[output]->add_input(source);
    }
  }
}

int main(int argc, char* argv[]) {
  string filename = aoc::dataFilename(argv[0], "user.input");
  ifstream in(filename);
  map<string, unique_ptr<pulse_module>, less<>> modules;
  getData(in, modules);
  for (int i = 0; i < 1000; i++) {
    pulse_module::push_button(modules);
  }
  cout << "Part 1 Pulse Product: " << pulse_module::pulse_product() << "\n";
  // Part two was partially spoiled.  Used graphviz to identify nodes which fed
  // the output node x.
  while ((modules["qt"]->first_low() < 0) || (modules["qb"]->first_low() < 0) ||
         (modules["mp"]->first_low() < 0) || (modules["ng"]->first_low() < 0)) {
    pulse_module::push_button(modules);
  }
  int64_t part2answer =
      std::lcm(modules["qt"]->first_low(), modules["qb"]->first_low());
  part2answer = lcm(part2answer, modules["mp"]->first_low());
  part2answer = lcm(part2answer, modules["ng"]->first_low());

  cout << "Part 2 complete after " << part2answer << " button presses.\n";
  return 0;
}
