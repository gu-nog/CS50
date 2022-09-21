# Skill log
#### Video Demo:  <URL HERE>
#### Description:
Vídeo: Skill log, Gustavo Nogueira Mendes, Belo Horizonte, Brazil and any other details<br>
Explain what each file and part of my code does<br>
What will your software do? Will permit any user to share and log what he is learning and also:
- make notes;
- books;
- contests;
- projects(private or public - explain the decisions);
- save public and private notes;
- create quizzes to remember;
- private or public profile;
How will it be executed? via website in Flask<br>
What new skills will you need to acquire? host my flask application online, use databases without cs50 library and other things I'll discover

## Activities:
[x] - basic template and application structure
[x] - login and signup
[x] - sessions

# Explanations:
## basictemplate.html:
Is my application default template implemented using jinja template pattern

## database.py:
- run_query: run a query in skilllog.db using sqlite3 library and returns false on error or the query result; this function can receive a query with '?' placeholder and tuple as 'params', such as cs50 library
- Why sqlite3: is a simple database that stay inside our application not on another server
- signup: add user to users table
- login: returns user id if exists with the same password or -1
- emailused: return true if email is registered in database
- nameused: return true if email is registered in database

## skilllog.db:
- table users: columns id(int), name(str), email(str), password(saves as text/str the hash of the passwords) and private(bool if the user allows other people knowing his name to see his log)

## login.html:
- GET: returns a form page to login(email and password)
- POST: verify email(with @, ., not empty and registered) and password(not empty and its hash matches with the one from the email user), if everything is correct on datas, start a session to user

## signup.html:
- GET: returns a form page to register(name, email, password, confirmation password and selector private or public)
- POST: verify name is not empty, email is not empty and have @ and ., password have len between 4-20 chars, confirmation password must match and be providaded and selector must have a valid value, if everything is ok, add to database the new user

## log.html:
- Via GET return the user's log

## Searchform.html:
- Via GET return a form with user field to search for someone's else log

## Otherlog.html:
- Via GET return the form of a user by his name

## Addlog.html:
- return a form to add an activity to your log and in POST can also contain an card of sucess or error messages

## edit.html:
- return a form to edit an activity of your log and in POST can also contain an card of sucess or error messages

## more.html:
- return an complete page with full title, description and notes of someone's activity

# index.html:
- GET: return an list of choices to what the user can do after logged in

## Styles.css:
- some basic styles linked to basic template