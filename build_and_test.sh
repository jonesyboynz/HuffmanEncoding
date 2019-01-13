echo -e "================================================"
echo -e "================== COMPILING ==================="
echo -e "================================================"
make all
echo -e "================================================"
echo -e "================ RUNNING TESTS ================="
echo -e "================================================"
./test
echo -e "================================================"
echo -e "============== SIMPLE TEST CASE ================"
echo -e "================================================"
./huff encode Test/Data/build_test_data build_test_output.out
echo -e "Before and After:"
stat -c '%n %s' Test/Data/build_test_data
stat -c '%n %s' build_test_output.out
echo -e "================================================"
echo -e "====== COMPLETE WORKS OF SHAKESPEARE ==========="
echo -e "================================================"
if [ -f "Test/Data/complete_works_of_shakespeare.ignore" ]
then
	echo -e "Complete works of Shakespeare has found."
else
	wget --tries=1 -O Test/Data/complete_works_of_shakespeare.ignore http://ocw.mit.edu/ans7870/6/6.006/s08/lecturenotes/files/t8.shakespeare.txt
fi
./huff encode Test/Data/complete_works_of_shakespeare.ignore complete_works_of_shakespeare.ignore.out
echo -e "Before and After:"
stat -c '%n %s' Test/Data/complete_works_of_shakespeare.ignore
stat -c '%n %s' complete_works_of_shakespeare.ignore.out
echo -e "================================================"
echo -e "=================== CLEANUP ===================="
echo -e "================================================"
rm -v build_test_output.out
rm -v complete_works_of_shakespeare.ignore.out
echo -e "================================================"
echo -e "=================== COMPLETE ==================="
echo -e "================================================"
