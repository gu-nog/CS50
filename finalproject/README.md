# Skill log
#### Video Demo:  <URL HERE>
#### Description:
Vídeo: Skill log, Gustavo Nogueira Mendes, Belo Horizonte, Brazil and any other details<br>
Explain what each file and part of my code does<br>
What will your software do? Will permit any user to share and log what he is learning and also:
- make notes and updload certificates of courses; 
- books; 
- contests;
- projects(private or public - explain the decisions);
- save public and private notes;
- create quizzes to remember; 
- private or public profile;
How will it be executed? via website in Flask<br>
What new skills will you need to acquire? save files on server, host my flask application online, use databases without cs50 library and other things I'll discover

## Activities:
[x] - basic template and application structure
[] - login and signup

# Explanations:
## basictemplate.html:
Is my application default template implemented using jinja template pattern
## database.py:
- run_query: run a query in skilllog.db using sqlite3 library and returns false on error or the query result; this function can receive a query with '?' placeholder and tuple as 'params', such as cs50 library
- Why sqlite3: is a simple database that stay inside our application not on another server

## skilllog.db:
- table users: columns id(int), name(str), email(str), password(saves as text/str the hash of the passwords) and private(bool if the user allows other people knowing his name to see his log)