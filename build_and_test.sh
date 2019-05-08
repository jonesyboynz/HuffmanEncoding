echo -e "\e[1m================================================"
echo -e "================== COMPILING ==================="
echo -e "================================================\e[21m"
make all
echo -e "\e[1m================================================"
echo -e "================ RUNNING TESTS ================="
echo -e "================================================\e[21m"
./test
if [ $? -ne 0 ]
then
  echo -e "\e[91mTests failed. Exiting!\e[39m"
  exit 1
fi
echo -e "\e[1m================================================"
echo -e "================= SMOKE TEST ==================="
echo -e "================================================\e[21m"
./huff encode Test/Data/build_test_data build_test_output.out
if [ $? -ne 0 ]
then
  echo -e "\e[91mSmoke test failed. Exiting!\e[39m"
  exit 1
fi
echo -e "\e[1m================================================"
echo -e "============== SIMPLE TEST CASE ================"
echo -e "================================================\e[21m"
echo -e "\e[96mEncoding...\e[39m"
./huff encode Test/Data/build_test_data2 build_test_output2.out
echo -e "\e[96mBefore and After:\e[39m"
stat -c '%n %s' Test/Data/build_test_data2
stat -c '%n %s' build_test_output2.out
echo -e "\e[96mComparison to expectation:\e[39m"
python3 Test/Runtime/compare-files.py build_test_output2.out Test/Data/build_test_data2_encoding_expectation
if [ $? -ne 0 ]
then
  echo -e "\e[91mSimple test case failed on encoding. Exiting!\e[39m"
  python3 Test/Runtime/binary-view.py Test/Data/build_test_data2_encoding_expectation
  python3 Test/Runtime/binary-view.py build_test_output2.out
  exit 1
fi
echo -e "\e[96mDecoding...\e[39m"
./huff decode build_test_output2.out build_test_output2_decoded.out
echo -e "\e[96mBefore and After:\e[39m"
stat -c '%n %s' build_test_output2.out
stat -c '%n %s' build_test_output2_decoded.out
echo -e "\e[96mComparison to expectation:\e[39m"
python3 Test/Runtime/compare-files.py build_test_output2_decoded.out Test/Data/build_test_data2
if [ $? -ne 0 ]
then
  echo -e "\e[91mSimple test case failed on decoding. Exiting!\e[39m"
  python3 Test/Runtime/binary-view.py Test/Data/build_test_data2
  python3 Test/Runtime/binary-view.py build_test_output2_decoded.out
  exit 1
fi
echo -e "\e[1m================================================"
echo -e "====== COMPLETE WORKS OF SHAKESPEARE ==========="
echo -e "================================================\e[21m"
if [ -f "Test/Data/complete_works_of_shakespeare.ignore" ]
then
	echo -e "\e[96mComplete works of Shakespeare has found.\e[39m"
else
	wget --tries=1 -O Test/Data/complete_works_of_shakespeare.ignore http://ocw.mit.edu/ans7870/6/6.006/s08/lecturenotes/files/t8.shakespeare.txt
fi
echo -e "\e[96mEncoding...\e[39m"
./huff encode Test/Data/complete_works_of_shakespeare.ignore encoded_complete_works_of_shakespeare.ignore.out
echo -e "\e[96mDecoding...\e[39m"
./huff decode encoded_complete_works_of_shakespeare.ignore.out decoded_complete_works_of_shakespeare.ignore.out
echo -e "\e[96mBefore and After:\e[39m"
stat -c '%n %s' Test/Data/complete_works_of_shakespeare.ignore
stat -c '%n %s' encoded_complete_works_of_shakespeare.ignore.out
stat -c '%n %s' decoded_complete_works_of_shakespeare.ignore.out
echo -e "\e[1m================================================"
echo -e "=================== CLEANUP ===================="
echo -e "================================================\e[21m"
rm -v build_test_output.out
rm -v encoded_complete_works_of_shakespeare.ignore.out
rm -v decoded_complete_works_of_shakespeare.ignore.out
echo -e "\e[1m================================================"
echo -e "=================== COMPLETE ==================="
echo -e "================================================\e[21m"
