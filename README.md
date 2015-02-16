# MyFtp

Simple FTP client written in C with server and client.

Very simple to use :

Launch the server with this command line
>./server port

Launch the client with this command line
>./client host port

The client handle the following commands:<br/>
<ul>
  <li>ls: list the current directory of the server.</li>
  <li>cd: change the current directory of the server.</li>
  <li>get _FILE_: copy the file _FILE_ from the server to the client.</li>
  <li>put _FILE_: copy the file _FILE_ from the client to the server.</li>
  <li>pwd: display the current directory of the server.</li>
  <li>quit: close the connection and stop the program.</li>
</ul>
