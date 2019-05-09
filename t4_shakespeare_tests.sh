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
echo -e "\e[96mBefore encoding, after encoding and after decoding:\e[39m"
stat -c 'Original: %n %s' Test/Data/complete_works_of_shakespeare.ignore
stat -c 'Encoded:  %n %s' encoded_complete_works_of_shakespeare.ignore.out
stat -c 'Decoded:  %n %s' decoded_complete_works_of_shakespeare.ignore.out
python3 Test/Runtime/compare-files.py decoded_complete_works_of_shakespeare.ignore.out Test/Data/complete_works_of_shakespeare.ignore
if [ $? -ne 0 ]
then
  echo -e "\e[91mDecoded file does not match original file.\e[39m"
  exit 1
fi