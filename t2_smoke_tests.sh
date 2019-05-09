./huff encode Test/Data/build_test_data build_test_output.out
if [ $? -ne 0 ]
then
  echo -e "\e[91mSmoke test failed.\e[39m"
  exit 1
fi
./huff decode build_test_output.out build_test_output_decoded.out
if [ $? -ne 0 ]
then
  echo -e "\e[91mSmoke test failed.\e[39m"
  exit 1
fi