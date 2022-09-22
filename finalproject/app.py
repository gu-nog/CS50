from distutils.log import error
from typing import final
from flask import Flask, render_template, request, redirect, session, escape
from flask_session import Session
from database import get_id, get_name, add_activity, delete_user, edit_activity, emailused, get_activities, get_activity, more_about, namepublic, nameused, adduser, verifyuser

app = Flask(__name__)
app.config["SESSION_PERMANENT"] = True
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

base_url = 'https://skill-log.herokuapp.com/'

colors = {"course": 'black', 'book': 'blue', 'contest': 'green', 'project': 'blueviolet'}

def authenticated():
    if 'user_id' in session.keys():
        return True
    return False

@app.route('/')
def index():
    global base_url
    if not authenticated():
        return redirect('/login')
    return render_template('index.html', name=get_name(session['user_id']), base_url = base_url)

@app.route('/logout')
def logout():
    if authenticated():
        session.clear()
    return redirect('/login')

@app.route('/login', methods=['POST', 'GET'])
def login():
    errors = {'email': '', 'password': ''}
    try:
        if request.method == 'GET':
            return render_template('login.html', errors=errors)
        else:
            email = request.form.get('email')
            password = request.form.get('password')

            # email is not empty and have @ and .
            if email == '':
                errors['email'] = 'Please, provide your email'
            elif email.count('@') == 0:
                errors['email'] = 'Emails must contain "@"!'
            elif email.count('.') == 0:
                errors['email'] = 'Emails must contain "."!'
            elif not emailused(email):
                errors['email'] = 'wrong password/email'
            
            # password have len between 4-20 chars
            if len(password) < 4:
                errors['password'] = 'Passwords must have more than 3 characters'
            elif len(password) > 20:
                errors['password'] = 'Passwords must have less than 21 characters'

            valid_data = (errors == {'email': '', 'password': ''})
            if valid_data:
                user_id = verifyuser(email, password)
                if user_id != -1:
                    session['user_id'] = user_id
                    session['editing'] = None
                    return redirect('/')
                else:
                    errors['email'] = 'wrong password/email'
                    return render_template('login.html', errors=errors)
            else:
                return render_template('login.html', errors=errors)
    except:
        return render_template('login.html', errors=errors, servererror=True)

@app.route('/signup', methods=['POST', 'GET'])
def signup():
    errors = {'name': '', 'email': '', 'password': '', 'verifypassword': '', 'visibility': ''}
    try:
        if request.method == 'GET':
            return render_template('signup.html', errors=errors)
        else:
            name = request.form.get('name')
            email = request.form.get('email')
            password = request.form.get('password')
            verifypassword = request.form.get('verifypassword')
            visibility = request.form.get('visibility')

            # name is not empty
            if name == '':
                errors['name'] = 'Please, provide an username'
            elif nameused(name):
                errors['name'] = 'This username has been used :('
            
            # email is not empty and have @ and .
            if email == '':
                errors['email'] = 'Please, provide your email'
            elif email.count('@') == 0:
                errors['email'] = 'Emails must contain "@"!'
            elif email.count('.') == 0:
                errors['email'] = 'Emails must contain "."!'
            elif emailused(email):
                errors['email'] = 'Email has been used :('
            
            # password have len between 4-20 chars
            if len(password) < 4:
                errors['password'] = 'Passwords must have more than 3 characters'
            elif len(password) > 20:
                errors['password'] = 'Passwords must have less than 21 characters'
            
            # confirmation password must match and be providaded
            if verifypassword == '':
                errors['verifypassword'] = 'Please, provide an confirmation password'
            elif verifypassword != password:
                errors['verifypassword'] = 'Passwords must match'
            
            # selector must have a valid value
            if visibility not in ['private', 'public']:
                errors['visibility'] = 'Unknown visibility'

            valid_data = (errors == {'name': '', 'email': '', 'password': '', 'verifypassword': '', 'visibility': ''})
            if valid_data:
                if adduser(name, email, password, visibility):
                    session['user_id'] = verifyuser(email, password)
                    return redirect('/')
                else:
                    return render_template('signup.html', errors=errors, servererror=True)
            else:
                return render_template('signup.html', errors=errors)
    except:
        return render_template('signup.html', errors=errors, servererror=True)

@app.route('/delete')
def delete_account():
    """finish session, delete all db info related to user and redirect to sign up page"""
    if not authenticated():
        return redirect('/login')
    if delete_user(session['user_id']):
        session.clear()
        return redirect('/signup')
    return redirect('/')

@app.route('/log/see')
def see_log():
    """The user can see his log here via GET"""
    global colors
    if not authenticated():
        return redirect('/login')
    log = get_activities(session['user_id'])
    return render_template('log.html', range_log_len=range(len(log)), log=log, colors=colors)

@app.route('/log/search')
def search_log():
    """Here the user can insert an username and if its profile is public, see it"""
    if not 'name' in request.args:
        return render_template('searchform.html', error=False, name=None)
    else:
        if not namepublic(request.args.get('name')):
            return render_template('searchform.html', error=True, name=request.args.get('name'))
        else:
            global colors
            log = get_activities(get_id(request.args.get('name')))
            final_log = []
            for activity in log:
                if activity[2] == False:
                    final_log.append(activity)
            return render_template('otherlog.html', range_log_len=range(len(final_log)), log=final_log, colors=colors)

@app.route('/log/add', methods=['post', 'get'])
def add_log():
    """The user can add an activity to log"""
    try:
        errors = {'title': '', 'activity_type': '', 'visibility': '', 'description': '', 'notes': '',
                'date': ''}
        if not authenticated():
            return redirect('/login')
        if request.method == 'GET':
            return render_template('addlog.html', errors=errors)
        else:
            title = request.form.get('title')
            activity_type = request.form.get('type')
            visibility = request.form.get('visibility')
            description = request.form.get('description')
            notes = request.form.get('notes')
            publicnotes = request.form.get('publicnotes') == 'public'
            date = request.form.get('date')  # YYYY-MM-DD

            # Title not empty and shorter than 100 chars
            if title == '':
                errors['title'] = 'Please, provide a title'
            elif len(title) > 100:
                errors['title'] = 'Please, provide a title with less than 100 characters'

            # Type selected and valid
            if activity_type == '--type--':
                errors['activity_type'] = 'Please, provide the type'
            elif not activity_type in ['course', 'book', 'contest', 'project']:
                errors['activity_type'] = 'Invalid type'

            # visibility valid
            if not visibility in ['private', 'public']:
                errors['visibility'] = 'Invalid visibility'

            # Description not empty and shorter than 500 chars
            if description == '':
                errors['description'] = 'Please, provide the description'
            elif len(description) > 750:
                errors['description'] = 'Please, write a description with less than 750 characters'

            # Notes shorter than 5000 chars
            if len(notes) > 5000:
                errors['notes'] = 'Please, only use 5000 characters to take notes'

            # Valid date            
            try:
                year = int(date[:4])
                month = int(date[5:7])
                day = int(date[-2:])
            except:
                errors['date'] = 'Please put an valid date'

            if errors == {'title': '', 'activity_type': '', 'visibility': '', 'description': '', 'notes': '',
                'date': ''}:
                add_activity(title, activity_type, visibility, description, notes, publicnotes, 
                             year, month, day, session['user_id'])
                return render_template('addlog.html', errors=errors, added=True)
            else:
                return render_template('addlog.html', errors=errors)
    except:
        return render_template('addlog.html', errors=errors, server_error=True)

@app.route('/edit', methods=['post', 'get'])
def edit_log():
    """User can edit a saved activity"""
    errors = {'title': '', 'activity_type': '', 'visibility': '', 'description': '', 'notes': '',
                'date': ''}
    try:
        if not authenticated():
            return redirect('/login')
        if request.method == 'GET':
            data = get_activity(request.args.get('id'), session['user_id'])
            session['editing'] = request.args.get('id')
            if len(data) == 0:
                return redirect('/log/see')
            final_data = list(data[0])
            if len(str(final_data[-1])) == 1:
                final_data[-1] = '0' + str(final_data[-1])
            else:
                final_data[-1] = str(final_data[-1])
            if len(str(final_data[-2])) == 1:
                final_data[-2] = '0' + str(final_data[-2])
            else:
                final_data[-2] = str(final_data[-2])
            return render_template('edit.html', errors=errors, data=final_data)
        else:
            title = request.form.get('title')
            activity_type = request.form.get('type')
            visibility = request.form.get('visibility')
            description = request.form.get('description')
            notes = request.form.get('notes')
            publicnotes = request.form.get('publicnotes') == 'public'
            date = request.form.get('date')  # YYYY-MM-DD

            # Title not empty and shorter than 100 chars
            if title == '':
                errors['title'] = 'Please, provide a title'
            elif len(title) > 100:
                errors['title'] = 'Please, provide a title with less than 100 characters'

            # Type selected and valid
            if activity_type == '--type--':
                errors['activity_type'] = 'Please, provide the type'
            elif not activity_type in ['course', 'book', 'contest', 'project']:
                errors['activity_type'] = 'Invalid type'

            # visibility valid
            if not visibility in ['private', 'public']:
                errors['visibility'] = 'Invalid visibility'

            # Description not empty and shorter than 500 chars
            if description == '':
                errors['description'] = 'Please, provide the description'
            elif len(description) > 750:
                errors['description'] = 'Please, write a description with less than 750 characters'

            # Notes shorter than 5000 chars
            if len(notes) > 5000:
                errors['notes'] = 'Please, only use 5000 characters to take notes'

            # Valid date            
            try:
                year = int(date[:4])
                month = int(date[5:7])
                day = int(date[-2:])
            except:
                errors['date'] = 'Please put an valid date'
            
            if errors == {'title': '', 'activity_type': '', 'visibility': '', 'description': '', 'notes': '',
                'date': ''}:
                edit_activity(title, activity_type, visibility, description, notes, publicnotes, 
                             year, month, day, session['user_id'], session['editing'])
                data = get_activity(session['editing'], session['user_id'])
                final_data = list(data[0])
                if len(str(final_data[-1])) == 1:
                    final_data[-1] = '0' + str(final_data[-1])
                else:
                    final_data[-1] = str(final_data[-1])
                if len(str(final_data[-2])) == 1:
                    final_data[-2] = '0' + str(final_data[-2])
                else:
                    final_data[-2] = str(final_data[-2])
                return render_template('edit.html', errors=errors, added=True, data=final_data)
            else:
                if len(str(month)) == 1:
                    month = '0' + str(month)
                else:
                    month = str(month)
                if (len(str(day))) == 1:
                    day = '0' + str(day)
                else:
                    day = str(day)
                return render_template('edit.html', errors=errors, 
                                        data=[title, activity_type, visibility=='private', description, notes, publicnotes == False, year, month, day])
    except:
        return render_template('edit.html', errors=errors, server_error=True, data=None)

@app.route('/more')
def more():
    if not 'id' in request.args:
        return redirect('/')
    else:
        try:
            origin = request.environ['HTTP_REFERER']
            informations = more_about(request.args.get('id'))[0]
            title = informations[0]
            description = informations[1]
            notes = informations[2]
            if informations[3] == True:
                notes = 'This notes is private!'
            return render_template('more.html', origin=origin, title=title, description=description, notes=notes)
        except:
            return redirect('/')

if __name__ == '__main__':
    app.config['TEMPLATES_AUTO_RELOAD'] = True
    app.config['SEND_FILE_MAX_AGE_DEFAULT'] = 0
    app.run(debug=True)
