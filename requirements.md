A simple command-line program to test remote IMAP server functionality. Process commands against any remote IMAP server and display to users to make it seem as though they're at the command line of a local Linux file system. 

# Example Session 

For an account robin@example.com with a password of pass...

	login> example.com robin pass
	robin@example.com/> 
	robin@example.com/> limit 20
	robin@example.com/> ls -s "test message"
	robin@example.com/> ls 3
	robin@example.com/> head 3
	robin@example.com/> cd sent
	robin@example.com/sent/> cd ..
	robin@example.com/> mv -s "test message" "test msg 1"
	robin@example.com/> mv 3 junk
	robin@example.com/> rm 2
	robin@example.com/> rm -s "test msg 1"
	robin@example.com/> head 1
	robin@example.com/> send robin@example.com "Test msg 2" "Hello, this is msg body"
	robin@example.com/> exit

The limit command limits the # of lines returned from any command. Default is 20. (Resizes a vector of strings.)

A message # may be the actual server Message-Id or the message # as returned by the last ls command. That is, 1 through 20, if there are 20 messages on our IMAP server. Keep a vector of strings to track the Message-Ids of the last ls command to use with later commands.

The ls command accepts flags for -from, -to, -subject or their abbreviations, -f, -t, -s. With no flag it's expecting a msg#. Output of ls has format of #-subject-from (where the # is based on the index into the vector of strings):

	1. "Test msg 1" robin@example.com 
	2. "Test msg 2" robin@example.com
	3. "Hello World" root@example.com

The mv command can move a message to a folder or rename its fields.

# Approach

1. Use strtok() or strstream or some other simple command parser in a for(;;) loop until the user enters "exit" 
1. Capable of building on Linux (and Windows using libunistd)
1. Use STL only as necessary 
1. Keep it simple

# Dependencies

1. C++
1. cmake
1. libetpan (or another suitable open source C/C++ IMAP library)
1. openssl