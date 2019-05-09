echo -e "\e[96mEncoding...\e[39m"
./huff encode Test/Data/build_test_data2 build_test_output2.out
echo -e "\e[96mBefore and After:\e[39m"
stat -c 'Original: %n %s' Test/Data/build_test_data2
stat -c 'Encoded:  %n %s' build_test_output2.out
echo -e "\e[96mComparison to expectation:\e[39m"
python3 Test/Runtime/compare-files.py build_test_output2.out Test/Data/build_test_data2_encoding_expectation
if [ $? -ne 0 ]
then
  echo -e "\e[91mSimple tests failed on encoding.\e[39m"
  python3 Test/Runtime/binary-view.py Test/Data/build_test_data2_encoding_expectation
  python3 Test/Runtime/binary-view.py build_test_output2.out
  exit 1
fi
echo -e "\e[96mDecoding...\e[39m"
./huff decode build_test_output2.out build_test_output2_decoded.out
echo -e "\e[96mBefore and After:\e[39m"
stat -c 'Encoded: %n %s' build_test_output2.out
stat -c 'Decoded: %n %s' build_test_output2_decoded.out
echo -e "\e[96mComparison to original:\e[39m"
python3 Test/Runtime/compare-files.py build_test_output2_decoded.out Test/Data/build_test_data2
if [ $? -ne 0 ]
then
  echo -e "\e[91mSimple tests failed on decoding.\e[39m"
  python3 Test/Runtime/binary-view.py Test/Data/build_test_data2
  python3 Test/Runtime/binary-view.py build_test_output2_decoded.out
  exit 1
fi