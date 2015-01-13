IRremote for multiple IR receivers
====
Allow arduino read data from multiple IR receivers

Default - 2 receivers
To change it max number go to CppList.cpp and change in void CppList::CppList variable _maxCount to your number.
Max receivers number - 4 (?; Really don't know)

This is modified version of original IRemote library.
For more than two receivers minor changes in timing constants were needed.