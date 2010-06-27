#!/bin/bash

# get filename for report
REPORT_FILE=$1
OUTPUT_FILE=`basename $1 .report`.output
if [ `uname -o` = "Msys" ]; then
  EXPECTED_RESULT=`echo "$2" | cut -d, -f 2`
else
  EXPECTED_RESULT=`echo "$2" | cut -d, -f 1`
fi
TARGET=$3
if [ ! "$4" = "--" ]; then
  echo "error: argument error, \$4 has to be '--'!"
  exit 2
fi
shift 4

# run simulavr, this uses all other arguments
echo "$*"
$* > ${REPORT_FILE}.stdout 2> ${REPORT_FILE}.stderr
RESULT=$?
cat ${REPORT_FILE}.stdout

# write report
cp ${REPORT_FILE}.stdout ${REPORT_FILE}
L=`wc -l ${REPORT_FILE}.stderr | cut "-d " -f 1`
if [ ! "$L" = "1" ]; then
  echo "-- stderr ----------------------------" >> ${REPORT_FILE} 
  cat ${REPORT_FILE}.stderr >> ${REPORT_FILE}
fi
rm -f ${REPORT_FILE}.stdout ${REPORT_FILE}.stderr

# give back exit code
RES=0
if [ ! "$RESULT" = "$EXPECTED_RESULT" ]; then
  echo ""
  echo "error: return code from simulavr = $RESULT, expected = $EXPECTED_RESULT!"
  echo ""
  cat ${REPORT_FILE}
  echo ""
  RES=1
fi
exit $RES

# EOF
