s="/***************************************\n"
s=$s"Author: spgoal\n"
d=`date +"%a, %b/%d/%G, %H:%M:%S"`
s=$s"Date: "$d"\n"
s=$s"Lang: C++\n"
s=$s"***************************************/\n"
echo -e $s > ttt
cat main.cpp >> ttt
mv -f ttt main.cpp
