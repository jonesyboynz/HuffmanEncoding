./test
if [ $? -ne 0 ]
then
  echo -e "\e[91mUnit testing failed.\e[39m"
  exit 1
fi