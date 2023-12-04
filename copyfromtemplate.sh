#/bin/bash

SCRIPT_DIR=$(dirname $(realpath "$0"))

function usage () {
  echo "Usage: $0 <year> <day>"
  echo 
  echo "  <year> - A number between 2021 and 2100 inclusive."
  echo "   <day> - A number between 01 and 25 inclusive."
  echo 
  echo "Example: $0 2021 01"
  exit 1
}

if [ "$1" -gt 2020 ] && [ "$1" -lt 2100 ] 
then
  if [ "$2" -gt 0 ] && [ "$2" -lt 26 ]
  then
    NEW_DAY="${1}day${2}"
    echo $NEW_DAY
  else
    echo "Expected  1 < day <= 25.  Actual day=$2"
    usage
  fi
else
  echo "Expected 2020 < year < 2100.  Actual year=$1"
  usage
fi
echo $SCRIPT_DIR
TEMPLATE_DIR=${SCRIPT_DIR}/template
DEST_DIR=${SCRIPT_DIR}/${NEW_DAY}

mkdir $DEST_DIR
touch $DEST_DIR/example.input
touch $DEST_DIR/user.input
cp ${TEMPLATE_DIR}/gui_template.cpp ${DEST_DIR}/gui_${NEW_DAY}.cpp
cp ${TEMPLATE_DIR}/template.cpp ${DEST_DIR}/${NEW_DAY}.cpp
cp ${TEMPLATE_DIR}/test_template.cpp ${DEST_DIR}/test_${NEW_DAY}.cpp
cp ${TEMPLATE_DIR}/CMakeLists.txt ${DEST_DIR}

sed -i "s/template/${NEW_DAY}/g" ${DEST_DIR}/CMakeLists.txt
sed -i "s/Template/Test${NEW_DAY}/g" ${DEST_DIR}/CMakeLists.txt
sed -i "s/template/${NEW_DAY}/g" ${DEST_DIR}/test_${NEW_DAY}.cpp


echo "add_subdirectory( ${NEW_DAY} )" >> CMakeLists.txt


