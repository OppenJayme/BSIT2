
#LS COMMAND
ls (displays all files)
ls -l (more detailed ls)
ls --help
clear
ls --all / ls -a (same thing)
ls -l --all / ls -l -a / ls -la (same  thing)

MAN COMMAND ("manual" page)
man ls (displays all parameters with detailed definition)

PWD (print working directory)
tells you what folder/directory you are in

CD (change directory)
cd Documents

touch (to create a new file) (refrain from using spaces, use underscore)
touch jans.txt
touch long_name_of_jansen.txt

nano (to open files)
nano l [tab] (tab to automatically fill in text)
Control X to finish/Exit 
^ = Control Key 

mkdir (make directory)
mkdir test 
ls -l

rm (remove file)
rm -r (delete folder/directory with prompt)
rm -rf (delete folder/directory with no prompt)

Type cygdrive64 in search bar
cd /cygdrive/m (Show all folders and files)
touch ivan.txt
rm ivan.txt

mkdir Linux

cd .. (go back one folder)

cat [name of file] (displays everything inside the file)

for((i = 0; i < 10; i++)); do touch file$i.doc; done

mv file1.doc something_else.doc (rename the file)
mv file2.doc ../ (moved to the above folder)

rmdir (will remove folder if folder is empty)

ln (file) (new file)
- Copies the contents of file into the new file

ln -s file.txt link.txt
- Links ln command that is used for linking files and directories to each other. ln command allows any number of new names to be created, all pointing to the same file or directory. You can then use any of these names to operate with the original file's data.
- meaning if u delete file.txt, the content in link.txt will also get deleted.
