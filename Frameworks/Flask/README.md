# Flask - Web Framework

Flask is a micro framework which provides barebones for web development and can be extended using extensions.\
Flask has three dependecies:

1. routing, debugging and Web Server Gateway interface(WSGI) => Werkzeug
2. Template support => Jinja2
3. command-line integration => Click.

## Basics

1. All flask applications must create and application instance. The webserver passes all requests it receives from clients to this object for handling, using a protocal called WSGI. application instance is an object of class Flask.
   The only required argument is name of the main module or package of the application.
   ```
    from flask import Flask
    app = Flask(__name__)
   ```
   The \_\_name\_\_ argument tells flask the main directory of the app and where to find other files like templates.
2. Routes and view functions:
   ```
   @app.route('route_address')
   def route_function():
   ```
   The line staring with @ is a python decorator. common use of decorators is to register functions as callbacks.
   Alternately following can also be used here:
   ```
   app.add_url_rule('/', 'index', index)
   ```
   Here return value of the index function is the response of the webserver to the client.\
   The address of the route can be used to pass parameters to the function as shown:
   ```
   @app.route('/user/<name>')
   def user(name):
       return 'hello, {}'.format(name)
   ```
3. You can run flask app by setting environment variable FLASK_APP to the main server file and then start server by flask run.

4. The request(from flask import request) object encapsulates the HTTP request sent by the client. Contexts enable Flask to make certain variables globally accessible to a thread without interfering with the other threads.\
   Multithreaded webservers start a pool of threads and choose a thread from which to handle the requests.

5. There are two contexts in flask: \
   i. The _application context_\
   contains current*app (application instance) and g(object that app can use for temp storage during handling a request. Resets at each request)\
   ii. The \_request context*\
   contains request (request object) and session(user session is a dictionary that the application can use to store values that are remembered between requests.)\
   Flask activates the application and request contexts before dispatching a request to the application and removes them after the request is handled.\
   When the application context is pushed, the current_app and g variables become available to the thread. Likewise when request context is pushed, request and session objects become available as well.\
   app_ctx = app.app_context()

6. app.url_map to view the available routes in the form of a hash-map.

   ```
   Map([<Rule '/' (HEAD, OPTIONS, GET) -> index>,
   <Rule '/static/<filename>' (HEAD, OPTIONS, GET) -> static>,
   <Rule '/user/<name>' (HEAD, OPTIONS, GET) -> user>])
   ```

   HEAD and OPTIONS are managed by flask.\
   static route is added by flask to give access to static files.

7. Request object contains:
   form, args, values, cookies, headers, files, get_data(), get_json(), blueprint, endpoint, method(GET/POST), scheme(http/https), host, path, query_string, full_path, url, base_url, remote_addr,environ(roaw WSGI env dict for the request)

8. Request Hooks: perform functions before or after requests. 4 request hooks supported by flask as decorators\
   i. before_request\
   ii. before_first_request\
   iii. after_request\
   iv. teardown_request\
   To share data between request hook functions and view functions is to use the g context global as storage.

9. Responses:
   ```
   return '<h1>stuff</h1>', response_code, headers
   ```
   flask provides make_response function for returning responses. Example:
   ```
   response = make_response('<h1>test<\h1>')
   response.set_cookie('answer', '42')
   return response
   ```
   There is a special type of response called redirect which returns a new URL for the browser to navigate to, indicated by 302 status code.\
   from flask import redirect

## Templates

Seperates the business logic and the presentation logic. Templates contains the response text with placeholders for dynamic stuff, which are provided by the request handler or view function.

1. Jinja2 template engine\
   {{ name|capitalize }} #capitalize filter.
   other filters available, safe, lower, upper, title, trip, striptags.
   https://jinja.palletsprojects.com/en/3.1.x/templates/#builtin-filters

   ```
   {% if user %}
    Hello {{ user }}!
   {% else %}
    Hello, stranger!
   {% endif %}

   {% for comment in comments %}
    <li> {{ comment }} </li>
   {% endfor %}
   ```

   macros: are like functions in python.

   ```
   {% macro render_comment(comment) %}
     <li> {{ comment }} </li>
   {% end_macro %}
   ```

   then can be rendered like `{{ render_comment(comment) }}`

   Macros can be written to a seperate file and can be imported later.\

   ```
   {% import 'macros.html' as macros %}
   which can be then used as
   {{ macros.render_comment(comment) }}
   ```

   To avoid code duplication frequently used portions of templates can be stored in different html file and can be included as:\
   {% include 'common.html' %}

   inheritance is also available by defining a base html and then overriding the blocks.

2. Flask bootstrap: bootstrap integration into flask.\
   bootstrap base template:\
   {% extends "bootstrap/base.html" %}\
   There are following available blocks in base template:\
   doc(entire html), html_attribs(attributes inside html tag), html(contents of html tag), head, title, metas, styles, body_attribs, body, navbar, content, scripts.\
   To extend a block use:\
   {% block scripts %}\
   {{ super() }}\
   \<script type="text/javascript" src="lol.js">\</script>\
   {% endblock %}

3. Custom Error Pages\
   @app.errorhandler(404)\
   def page_not_found(e):\
   return render_template('404.html'), 404

4. url_for('user', name='john' ,\_external=True) would return http://localhost:5000/user/john
   if \_external is false then it will return /user/john.\
   Extra arguments will be added to the query string.

5. Static files - support static files such as js files, css and images etc. Looks for the files in static directory. Can be used as:
   \<link rel="stylesheet" href="{{ url_for('static', filename='css/styles.css') }}" >

6. Flask-Moment : integration of moment.js into flask. Useful for handling timezones.\
   {% block scripts %}\
   {{ super() }}\
   {{ moment.include_moment() }}\
   {% endblock %}\

\<p>The local date and time is {{ moment(current_time).format('LLL') }}.\</p>\
\<p>That was {{ moment(current_time).fromNow(refresh=True) }}\</p>\
format function renders the date and time according to the client's local timezone. current_time is passed as datetime.utcnow()\
moment js documentation: http://momentjs.com/docs/#/displaying/

## Web Forms

1. Use flask-wtf library for dealing with webforms. This requires a secret key configured in the app: app.config['SECRET_KEY'] = 'string'.\
   app.config is a general pupose dictionary to store conf variables used by flask, extensions or application itself. \
   The secret key is part of mechanism to protect against CSRF attacks.

2. Form Classes: each form is represented by a class that inherits from the class FlaskForm. This contains lists of fields in the form as objects and each of these objects can have validators attached.

   ```
   from flask_wtf import FlaskForm
   from wtforms import StringField, SubmitField
   from wtforms.validators import DataRequired
   class NameForm(FlaskForm):
       name = StringField('What is your Name?', validators=[DataRequired()])
       submit = SubmitField('Submit')
   ```

   following fields are available: BooleanField, DateField, DateTimeField, DecimalField, FileField, HiddenField, MultipleFileField, FieldList, FloatField,
   FormField, IntegerField, PasswordField, RadioField, SelectField, SelectMultipleField, SubmitField, StringField, TextAreaField\
   Following validators are available: DataRequired, Email, EqualTo, InputRequired,IPAddress, Lenght, MacAddress, NumberRange, Optional, Regexp, URL, UUID, AnyOf, NoneOf\

3. The forms generated using above can be rendered as HTML as shown:\

   ```
   <form>
      {{ form.hidden_tag() }}
      {{ form.name.label }} {{ form.name(id='my-text-field') }}
      {{ form.submit() }}
   </form>
   ```

   Another way is to use the bootstrap like so:

   ```
   {% import "bootstrap/wtf.html" as wtf %}
   {{  wtf.quick_form(form) }}
   ```

4. Form Handling in view functions.

   ```
   name = None
   form = NameForm()
   if form.validate_on_submit():
      name = form.name.data
      form.name.data = ''
   return render_template('index.html', form=form, name=name)
   ```

5. As during form submit, the page refreshes the request is sent to the server for handling. Then response is returned to the client. But when client refreshes the page, same post request is repeated by the client's browser, which is not desirable. To handle this response is returned using redirect.\
   Also when redirecting the data received from the form will be lost, that data can be stored in the user sessions.

   ```
   if form.validate_on_submit():
      session['name'] = form.name.data
      return redirect(url_for('index'))
   return render_template('index.html', form=form, name=session.get('name'))
   ```

6. Message Flashing: the flash displays a message to the user based on the handling of the form.\
   ```
   flash('Looks like you have changed your name!')
   ```
   these messages are displayed in templates using:
   ```
   {% for message in get_flashed_messages() %}
   <div class="alert alert-warning">
        <button type="button" class="close" data-dismiss="alert">&times;\</button>
        {{ message }}
   </div>
   ```

## Databases

1. Database abstraction layer packages such as SQLAlchemy or MongoEngine, that allow you to work at higher level with regular python objects instead of database entities such as tables, documents or query languages.

2. SQLAlchemy documentation:\
    https://flask-sqlalchemy.palletsprojects.com/en/3.1.x/\
   http://www.sqlalchemy.org/\
   SQLAlchemy is a powerful relational database framework that suports several database backends. It offers high-level ORM(object relational mappers- convert high level language constructs to low level DB instructions.) and low-level access to DB's native SQl functionality.\
   Paths for different backends:\
   -> MySQL : mysql://username:password@hostname/database\
   -> PostGres : postgresql://username:password@hostname/database\
   -> SQLite(Linux) : sqlite:////absolute/path/to/db\
   -> SQLite(Windows) : sqlite:///c:/absolute/path/to/db\
   these paths should be stored in app.config['SQLALCHEMY_DATABASE_URI'].\
   set app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] to false to use less memory unless signals for object changes are needed.\
   See documentation for more configuration fields.\
   Then initialize db = SQLAlchemy(app)

3. Model Definition:\
   The model is used when referring to persistent entities used by the application. In context of ORM, a model is typically a Python class with attributes that match the columns of a corresponding DB table.\

   ```
   class Role(db.Model):
       __tablename__ = 'roles'
       id = db.Column(db.Integer, primary_key=True)
       name = db.Column(db.String(64), unique=True)

       def __repr__(self):
           return '<Role %r>' % self.name
   ```

   SQLAlchemy column types: Integer, SmallInteger, BigInteger, Float, Numeric, String, Text, Unicode, UnicodeText, Boolean, Date, Time, DateTime, Interval, Enum, PickleType, LargeBinary.\
   SQLAlchemy column config types: primary_key, unique, index, nullable, default.\
   SQLAlchemy relationship options: backref, primaryjoin, lazy, uselist, order_by, secondary, secondaryjoin.\
   Foreign Key relationships handling:

   ```
   class Role(db.Model):
       ...
       users = db.relationship('User', backref='role')

    class User(db.Model):
        ...
        role_id = db.Column(db.Integer, db.ForeignKey('roles.id'))
   ```

4. DB operations:\

   ```
   # creating and destroying tables
   db.create_all()
   db.drop_all()

   # inserting rows
   admin_role = Role(name='Admin')
   user_john = User(username='john', role=admin_role)
   db.session.add(admin_role)
   db.session.add(user_john)
   db.session.add_all([admin_role, user_john])
   db.session.commit()

   # modifying rows
   admin_role.name = 'Administrator'
   db.session.add(admin_role)
   db.sesion.commit()

   # deleting rows
   db.session.delete(mod_role)
   db.session.commit()

   # querying rows
   Role.query.all()
   User.query.file_by(role=user_role).all()
   str(User.query.filter_by(role=user_role)) #native SQL command
   Role.query.filter_by(name='User').first() # results first or None

   ```

   Common SQLAlchemy query filters: filter(), filter_by(), limit(), offset(), order_by(), group_by()\
   Common SQLAlchemy query executors: all(), first(), first_or_404(), get(), get_or_404(), count(), paginate() {returns a Pagination object that contains the specified number of results}\
   pass lazy='dynamic' in the relationship() in the Model so it does not run the query but returns the query which can then be executed using query executors.

5. To add objects to import list of flask shell, use shell_context_processor decorator as below:

   ```
   @app.shell_context_processor
   def make_shell_context():
       return dict(db=db, User=User, Role=Role)
   ```

6. A database migration framework keeps track of changes to a database schema, allowing incremental changes to be applied. with SQLAlchemy Alembic can be used, or flask-migrate package can be used which is wrapper of Alembic.
   ```
   from flask_migrate import Migrate
   migrate = Migrate(app, db)
   ```
   then in command line use flask db init to add support for database migrations. This command creates migrations directory where migration scripts are kept.

## Email

1. smtplib can be used to send mail from flask. But flask-mail can be used. Add SMTP configuration to the app.config:

   ```
   app.config['MAIL_SERVER'] = 'smtp.googlemail.com'
   app.config['MAIL_PORT'] = 587
   app.config['MAIL_USE_TLS'] = True
   app.config['MAIL_USERNAME'] = os.environ.get('MAIL_USERNAME')
   app.config['MAIL_PASSWORD'] = os.environ.get('MAIL_PASSWORD')
   #export MAIL_USERNAME=<username> or set MAIL_USERNAME=<username>
   ```

   Then to send mail:

   ```
   app.config['FLASKY_MAIL_SUBJECT_PREFIX'] = '[Flasky]'
   app.config['FLASKY_MAIL_SENDER'] = 'Flasky Admin <flasky@example.com>'

   def send_email(to, subject, template, **kwargs):
       msg = Message(app.config['FLASKY_MAIL_SUBJECT_PREFIX'] + subject,
       sender=app.config['FLASKY_MAIL_SENDER'], recipients=[to])
       msg.body = render_template(template + '.txt', **kwargs)
       msg.html = render_template(template + '.html', **kwargs)
       mail.send(msg)
   ```

   Sending mail async:

   ```
    from threading import Thread

    def send_async_email(app, msg):
        with app.app_context():
        mail.send(msg)

    def send_email(to, subject, template, **kwargs):
        msg = Message(app.config['FLASKY_MAIL_SUBJECT_PREFIX'] + subject,
        sender=app.config['FLASKY_MAIL_SENDER'], recipients=[to])
        msg.body = render_template(template + '.txt', **kwargs)
        msg.html = render_template(template + '.html', **kwargs)
        thr = Thread(target=send_async_email, args=[app, msg])
        thr.start()
        return thr
   ```

   The execution of send_async_mail can be sent to a Celery task queue, if application needs to send bulk emails.

## Large Application Structure

```
|-flasky
    |-app/
        |-templates/
        |-static/
        |-main/
            |-__init__.py
            |-errors.py
            |-forms.py
            |-views.py
        |-__init__.py
        |-email.py
        |-models.py
        |-migrations/
        |-tests/
            |-__init__.py
            |-test*.py
        |-venv/
        |-requirements.txt
        |-config.py
        |-flasky.py
```

config.py contains the configuration class.

```
import os
basedir = os.path.abspath(os.path.dirname(__file__))
class Config:
    SECRET_KEY = os.environ.get('SECRET_KEY') or 'hard to guess string'
    MAIL_SERVER = os.environ.get('MAIL_SERVER', 'smtp.googlemail.com')
    MAIL_PORT = int(os.environ.get('MAIL_PORT', '587'))
    MAIL_USE_TLS = os.environ.get('MAIL_USE_TLS', 'true').lower() in \
    ['true', 'on', '1']
    MAIL_USERNAME = os.environ.get('MAIL_USERNAME')
    MAIL_PASSWORD = os.environ.get('MAIL_PASSWORD')
    FLASKY_MAIL_SUBJECT_PREFIX = '[Flasky]'
    FLASKY_MAIL_SENDER = 'Flasky Admin <flasky@example.com>'
    FLASKY_ADMIN = os.environ.get('FLASKY_ADMIN')
    SQLALCHEMY_TRACK_MODIFICATIONS = False

    @staticmethod
    def init_app(app):
        pass

class DevelopmentConfig(Config):
    DEBUG = True
    SQLALCHEMY_DATABASE_URI = os.environ.get('DEV_DATABASE_URL') or \
    'sqlite:///' + os.path.join(basedir, 'data-dev.sqlite')

class TestingConfig(Config):
    TESTING = True
    SQLALCHEMY_DATABASE_URI = os.environ.get('TEST_DATABASE_URL') or \
    'sqlite://'

class ProductionConfig(Config):
    SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL') or \
    'sqlite:///' + os.path.join(basedir, 'data.sqlite')

config = {
'development': DevelopmentConfig,
'testing': TestingConfig,
'production': ProductionConfig,
'default': DevelopmentConfig
}
```

Set configuration variables in environment variables for production, but for dev can use hardcoded values.

### Application Package:

This section contains application code, templates and static files of the project. The 'app' folder in the example above.

```
# application package constructor : app/__init__.py
# application factory which can be called from a script

from flask import Flask, render_template
from flask_bootstrap import Bootstrap
from flask_mail import Mail
from flask_moment import Moment
from flask_sqlalchemy import SQLAlchemy
from config import config
bootstrap = Bootstrap()
mail = Mail()
moment = Moment()
db = SQLAlchemy()
def create_app(config_name):
    app = Flask(__name__)
    app.config.from_object(config[config_name])
    config[config_name].init_app(app)
    bootstrap.init_app(app)
    mail.init_app(app)
    moment.init_app(app)
    db.init_app(app)
    # attach routes and custom error pages here

    from .main import main as main_blueprint
    app.register_blueprint(main_blueprint)
    return app
```

Then the routes and error page handlers can be implemented using blueprints. A blueprint is similar to an application in that it can also define routes and error handlers. When these are defined in a blueprint they are int a dormant state until the blueprint is registered with an application, at which point they become part of it. Using a blueprint defined in the global scope, the routes and error handlers of the application can be defined in almost the same way as in the single-script application.

```
# app/main/__init__.py main blueprint creation
from flask import Blueprint
# Blueprint takes name of the blueprint and the module's name where the blueprint is located.
main = Blueprint('main', __name__)
from . import views, errors
```

Then the main blueprint is registered inside the create_app function above.

```
def create_app(config_name):
    # ...
    from .main import main as main_blueprint
    app.register_blueprint(main_blueprint)
    return app
```

Add error handlers in the errors.py module.
to install application wide error handlers, @app_errorhandler must be used.

```
# app/main/errors.py

from flask import render_template
from . import main

@main.app_errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

@main.app_errorhandler(500)
def internal_server_error(e):
    return render_template('500.html'), 500
```

Define routes inside the main.py module. The redirect function now takes url_for('blueprint.view')

```
from datetime import datetime
from flask import render_template, session, redirect, url_for
from . import main
from .forms import NameForm
from .. import db
from ..models import User

@main.route('/', methods=['GET', 'POST'])
def index():
    form = NameForm()
    if form.validate_on_submit():
        # ...
        return redirect(url_for('.index'))
    return render_template('index.html',
                            form=form, name=session.get('name'),
                            known=session.get('known', False),
                            current_time=datetime.utcnow())
```

### Application Script

```
#flasky.py main script
import os
from app import create_app, db
from app.models import User, Role
from flask_migrate import Migrate
app = create_app(os.getenv('FLASK_CONFIG') or 'default')
migrate = Migrate(app, db)

@app.shell_context_processor
def make_shell_context():
    return dict(db=db, User=User, Role=Role)

```

To run the application set FLASK_APP=flasky.py, set FLASK_DEBUG=1

### Requirements file

Add requirements from the pip freeze >requirements.txt
which can then be installed using pip install -r requirements.txt

### Unit tests

The unit tests can be written like following:

```
import unittest
from flask import current_app
from app import create_app, db

# the methods that start with test_ are executed as tests.
# docs : https://docs.python.org/3/library/unittest.html

class BasicsTestCase(unittest.TestCase):
    def setUp(self):
        self.app = create_app('testing')
        self.app_context = self.app.app_context()
        self.app_context.push()
        db.create_all()

    def tearDown(self):
        db.session.remove()
        db.drop_all()
        self.app_context.pop()

    def test_app_exists(self):
        self.assertFalse(current_app is None)

    def test_app_is_testing(self):
        self.assertTrue(current_app.config['TESTING'])
```

To run the unit tests, a custom command can be added to flasky.py main script:

```
# to run the command on cmd use flask test
@app.cli.command()
def test():
    """Run the unit tests."""
    import unittest
    tests = unittest.TestLoader().discover('tests')
    unittest.TextTestRunner(verbosity=2).run(tests)
```

### Running the app

The application can be run as usual using flask run.\
The environment variables can be added to ~/.bashrc file.

## Authentication System

1. Packages used for authentication:
<ul>
    <li>Flask-Login: Management of user sessions for logged-in users.
    <li>WerkZeug, bcrypt, passlib: Password hashing and verification
    <li>itsdangerous: Cryptographyically secure token generation and verification
</ul>

2. Password Security:

   ```
   from werkzeug.security import generate_password_hash, check_password_hash
   class User(db.Model):
       # ...
       password_hash = db.Column(db.String(128))

       @property
       def password(self):
           raise AttributeError('password is not a readable attribute')

       @password.setter
       def password(self, password):
           self.password_hash = generate_password_hash(password)

       def verify_password(self, password):
           return check_password_hash(self.password_hash, password)
   ```

3. Auth Blueprint can be created as follows:

   ```
   # app/auth/__init__.py
   from flask import Blueprint
   auth = Blueprint('auth', __name__)
   from . import views

   # app/auth/view.py
   from flask import render_template
   from . import auth
   @auth.route('/login')
   def login():
       # store the login.html in templates/auth/ directory
       return render_template('auth/login.html')
   ```

   then in the app the blueprint can be used.

   ```
   # app/__init__.py

   def create_app(config_name):
       # ...
       from .auth import auth as auth_blueprint
       # here url_prefix is is used to register all routes with given prefix
       # so effective url will be  http://localhost:5000/auth/login
       app.register_blueprint(auth_blueprint, url_prefix='/auth')
       return app
   ```

4. User Auth using flask-login\
   The methods that need to be implemented: is_authenticated, is_active, is_anonymous, get_id\
   use UserMixin base class that is provided by the flask-login package.

   ```
   # app/models.py
   class User(UserMixin, db.Model):
       __tablename__ = 'users'
       id = db.Column(db.Integer, primary_key = True)
       email = db.Column(db.String(64), unique=True, index=True)
       username = db.Column(db.String(64), unique=True, index=True)
       password_hash = db.Column(db.String(128))
       role_id = db.Column(db.Integer, db.ForeignKey('roles.id'))
   ```

   Then inside the main app factory:

   ```
   # app/__init__.py
   from flask_login import LoginManager
   login_manager = LoginManager()
   login_manager.login_view = 'auth.login'
   def create_app(config_name):
       # ...
       login_manager.init_app(app)
       # ...
   ```

   then again in models file:

   ```
   from . import login_manager
   @login_manager.user_loader
   def load_user(user_id):
       return User.query.get(int(user_id))
   ```

   To protect routes we can use the following code:

   ```
   from flask_login import login_required
   @app.route('/secret')
   @login_required
   def secret():
       return 'Only authenticated users are allowed!'
   ```

5. Login form:
   The login form can be created using flask-form:

   ```
   # app/auth/forms.py

   from flask_wtf import FlaskForm
   from wtforms import StringField, PasswordField, BooleanField, SubmitField
   from wtforms.validators import DataRequired, Length, Email

   class LoginForm(FlaskForm):
       email = StringField('Email', validators=[DataRequired(), Length(1, 64),Email()])
       password = PasswordField('Password', validators=[DataRequired()])
       remember_me = BooleanField('Keep me logged in')
       submit = SubmitField('Log In')
   ```

   in the base template, we can use the current_user's status for authentication:

   ```
   # app/templates/base.html
   <ul class="nav navbar-nav navbar-right">
        {% if current_user.is_authenticated %}
        <li><a href="{{ url_for('auth.logout') }}">Log Out</a></li>
        {% else %}
        <li><a href="{{ url_for('auth.login') }}">Log In</a></li>
        {% endif %}
    </ul>
   ```

   The current_user variable is automatically available to all the view functions and templates by flask-login. the variable contains current logged in user or proxy anonymous user.

6. Signing users in:\
   The users can be signed in using the following piece of code:

   ```
    # app/auth/views.py
    from flask import render_template, redirect, request, url_for, flash
    from flask_login import login_user
    from . import auth
    from ..models import User
    from .forms import LoginForm
    @auth.route('/login', methods=['GET', 'POST'])
    def login():
        form = LoginForm()
        if form.validate_on_submit():
            user = User.query.filter_by(email=form.email.data).first()
            if user is not None and user.verify_password(form.password.data):
                login_user(user, form.remember_me.data)
                next = request.args.get('next')
                if next is None or not next.startswith('/'):
                    next = url_for('main.index')
                return redirect(next)
            flash('Invalid username or password.')
        return render_template('auth/login.html', form=form)
   ```

   the remember me boolean is used to save the value in long term cookie in user's browser. The optional REMEMBER_COOKIE_DURATION configuration option can be used to change the default one-year duration for the remember cookie.\
   The login template can be updated as follows:

   ```
    // app/templates/auth/login.html
    {% extends "base.html" %}
    {% import "bootstrap/wtf.html" as wtf %}

    {% block title %}Flasky - Login{% endblock %}
    {% block page_content %}
    <div class="page-header">
        <h1>Login</h1>
    </div>
    <div class="col-md-4">
        {{ wtf.quick_form(form) }}
    </div>
    {% endblock %}
   ```

7. Logging out users:
   The logout route can be implemented as follows:

   ```
    # app/auth/views.py
    from flask_login import logout_user, login_required
    @auth.route('/logout')
    @login_required
    def logout():
        logout_user()
        flash('You have been logged out.')
        return redirect(url_for('main.index'))
   ```

8. Registering Users:\
   The registration form can be added as follows:

   ```
    # app/auth/forms.py
    from flask_wtf import FlaskForm
    from wtforms import StringField, PasswordField, BooleanField, SubmitField
    from wtforms.validators import DataRequired, Length, Email, Regexp, EqualTo
    from wtforms import ValidationError
    from ..models import User

    class RegistrationForm(FlaskForm):
        email = StringField('Email', validators=[DataRequired(), Length(1, 64), Email()])
        username = StringField('Username', validators=[
                                DataRequired(), Length(1, 64),
                                Regexp('^[A-Za-z][A-Za-z0-9_.]*$', 0,
                                'Usernames must have only letters, numbers, dots or '
                                'underscores')])
        password = PasswordField('Password', validators=[
                                DataRequired(), EqualTo('password2', message='Passwords must match.')])
        password2 = PasswordField('Confirm password', validators=[DataRequired()])
        submit = SubmitField('Register')

        def validate_email(self, field):
            if User.query.filter_by(email=field.data).first():
            raise ValidationError('Email already registered.')

        def validate_username(self, field):
            if User.query.filter_by(username=field.data).first():
            raise ValidationError('Username already in use.')

   ```

   in the login form:

   ```
    <p>
        New user?
        <a href="{{ url_for('auth.register') }}">
            Click here to register
        </a>
    </p>
   ```

   The register view can then be added as:

   ```
    # app/auth/views.py
    @auth.route('/register', methods=['GET', 'POST'])
    def register():
        form = RegistrationForm()
        if form.validate_on_submit():
            user = User(email=form.email.data,
            username=form.username.data,
            password=form.password.data)
            db.session.add(user)
            db.session.commit()
            flash('You can now login.')
            return redirect(url_for('auth.login'))
        return render_template('auth/register.html', form=form)
   ```

9. Account Confirmation: The confirmation tokens can be generated using itsdangerous
   the default validity time of the tokens is one hour.

   ```
    # app/models.py
    from itsdangerous import TimedJSONWebSignatureSerializer as Serializer
    from flask import current_app
    from . import db
    class User(UserMixin, db.Model):
        # ...
        confirmed = db.Column(db.Boolean, default=False)
        def generate_confirmation_token(self, expiration=3600):
            s = Serializer(current_app.config['SECRET_KEY'], expiration)
            return s.dumps({'confirm': self.id}).decode('utf-8')

        def confirm(self, token):
            s = Serializer(current_app.config['SECRET_KEY'])
            try:
                data = s.loads(token.encode('utf-8'))
            except:
                return False
            if data.get('confirm') != self.id:
                return False
            self.confirmed = True
            db.session.add(self)
            return True
   ```

   The confirmation emails can be sent using the following piece of code:

   ```
    from ..email import send_email

    @auth.route('/register', methods=['GET', 'POST'])
    def register():
        form = RegistrationForm()
        if form.validate_on_submit():
            # ...
            db.session.add(user)
            db.session.commit()
            token = user.generate_confirmation_token()
            send_email(user.email, 'Confirm Your Account',
                        'auth/email/confirm', user=user, token=token)
            flash('A confirmation email has been sent to you by email.')
            return redirect(url_for('main.index'))
        return render_template('auth/register.html', form=form)
   ```

   The auth/email/confirm.txt is the text body of the confirmation email:

   ```
    Dear {{ user.username }},
    Welcome to Flasky!
    To confirm your account please click on the following link:
    {{ url_for('auth.confirm', token=token, _external=True) }}
    Sincerely,
    The Flasky Team
    Note: replies to this email address are not monitored.
   ```

   The view that confirms the user is as follows:

   ```
    from flask_login import current_user
    @auth.route('/confirm/<token>')
    @login_required
    def confirm(token):
        if current_user.confirmed:
            return redirect(url_for('main.index'))
        if current_user.confirm(token):
            db.session.commit()
            flash('You have confirmed your account. Thanks!')
        else:
            flash('The confirmation link is invalid or has expired.')
        return redirect(url_for('main.index'))
   ```

   To prevent unconfirmed user's from accessing the pages we can use before_app_request:

   ```
    # app/auth/views.py
    @auth.before_app_request

    def before_request():
        if current_user.is_authenticated \
                and not current_user.confirmed \
                and request.blueprint != 'auth' \
                and request.endpoint != 'static':
            return redirect(url_for('auth.unconfirmed'))

    @auth.route('/unconfirmed')
    def unconfirmed():
        if current_user.is_anonymous or current_user.confirmed:
            return redirect(url_for('main.index'))
        return render_template('auth/unconfirmed.html')
   ```

   The resending of confirmation link can be achieved by the following code:

   ```
    # app/auth/views.py
    @auth.route('/confirm')
    @login_required
    def resend_confirmation():
        token = current_user.generate_confirmation_token()
        send_email(current_user.email, 'Confirm Your Account',
                    'auth/email/confirm', user=current_user, token=token)
        flash('A new confirmation email has been sent to you by email.')
        return redirect(url_for('main.index'))
   ```

   Password updates, password resets, email address changes can be provided using similar code.

## Application Programming Interfaces (API)

1. REST(Representational State Transfer) has following characteristics:

   - Client Server
   - Stateless
   - Cache
   - Uniform interface
   - Layered System
   - Code-on-demand

2. Request Methods:

   - GET
   - POST
   - PUT
   - DELETE

3. Request and response body:

   - Json and xml are used commonly.
   - In a well designed RESTful API, the client knows a short list of top-level resource URLs and then discovers the rest from links included in responses, similar to how you can discover new web pages while browsing the web by clicking on links that appear in pages that you know about.

4. Use versioning in case of API development like /api/v1/posts

5. API blueprint structure:

   ```
   |-flasky
       |-app/
           |-api
               |-__init__.py
               |-users.py
               |-posts.py
               |-comments.py
               |-authentication.py
               |-errors.py
               |-decorators.py
   ```

   API blueprint creation:

   ```
   # app/api/__init__.py
   from flask import Blueprint
   api = Blueprint('api', __name__)
   from . import authentication, posts, users, comments, errors

   #app/init.py
   def create_app(config_name):
       # ...
       from .api import api as api_blueprint
       app.register_blueprint(api_blueprint, url_prefix='/api/v1')
       # ..
   ```

6. Response codes: A RESTful web service informs the client of the status of a request by sending the appropriate HTTP status code in the response, plus any additional information in the response body. Typical status codes:<ul>

   - 200 : Request completed
   - 201 : Request completed and new resource completed
   - 202 : Request accepted, in progress will run async.
   - 204 : No content , request completed but no data in response
   - 400 : Bad Request
   - 401 : Unauthorized
   - 403 : Forbidden - 404 : Not found
   - 405 : Method not allowed
   - 500 : Internal Server Error
    </ul>
   For returning in case of error in api this code can be used for handling:

   ```
       #app/api/errors.py
       def page_not_found(e):
           if request.accept_mimetypes.accept_json and \
                   not request.accept_mimetypes.accept_html:
               response = jsonify({'error': 'not found'})
               response.status_code = 404
               return response
           return render_template('404.html'), 404
   ```

7. Authentication with Flask-HTTPAuth

   - With HTTP authentication the credentials are included in auth header with all requests
   - Use the flask-httpauth as follows:

     ```
         # app/api/authentication.py
         from flask_httpauth import HTTPBasicAuth
         auth = HTTPBasicAuth()

         @auth.verify_password
         def verify_password(email, password):
             if email == '':
                 return False
             user = User.query.filter_by(email = email).first()
             if not user:
                 return False
             g.current_user = user
             return user.verify_password(password)

         # error handler:
         from .errors import unauthorized
         @auth.error_handler
         def auth_error():
             return unauthorized('Invalid credentials')
     ```

   - To protect a route, the auth.login_required decorator is used:
     ```
     @api.route('/posts/')
     @auth.login_required
     def get_posts():
         pass
     ```
   - since all the routes in blueprint need to be protected the login_required can be used once in a before_request handler:
     ```
         from .errors import forbidden
         @api.before_request
         @auth.login_required
         def before_request():
             if not g.current_user.is_anonymous and \
                     not g.current_user.confirmed:
             return forbidden('Unconfirmed account')
     ```

8. Token based authentication:

   ```
   class User(db.Model):
   # ...
   def generate_auth_token(self, expiration):
       s = Serializer(current_app.config['SECRET_KEY'],
       expires_in=expiration)
       return s.dumps({'id': self.id}).decode('utf-8')

   @staticmethod
   def verify_auth_token(token):
       s = Serializer(current_app.config['SECRET_KEY'])
       try:
           data = s.loads(token)
       except:
           return None
       return User.query.get(data['id'])

   # app/api/athentication.py
   @auth.verify_password
   def verify_password(email_or_token, password):
       if email_or_token == '':
           return False
       if password == '':
           g.current_user = User.verify_auth_token(email_or_token)
           g.token_used = True
           return g.current_user is not None
       user = User.query.filter_by(email=email_or_token).first()
       if not user:
           return False
       g.current_user = user
       g.token_used = False
       return user.verify_password(password)
   ```

   write to_json methods in the db models such as:

   ```
    class Post(db.Model):
        # ...
        def to_json(self):
            json_post = {
                'url': url_for('api.get_post', id=self.id),
                'body': self.body,
                'body_html': self.body_html,
                'timestamp': self.timestamp,
                'author_url': url_for('api.get_user', id=self.author_id),
                'comments_url': url_for('api.get_post_comments', id=self.id),
                'comment_count': self.comments.count()
            }
            return json_post
   ```

9. Implementing resource endpoints:

   ```
   # app/api/posts.py
   @api.route('/posts/')
   def get_posts():
       posts = Post.query.all()
       return jsonify({ 'posts': [post.to_json() for post in posts] })

   @api.route('/posts/<int:id>')
   def get_post(id):
       post = Post.query.get_or_404(id)
       return jsonify(post.to_json())

   @api.route('/posts/', methods=['POST'])
   @permission_required(Permission.WRITE)
   def new_post():
       post = Post.from_json(request.json)
       post.author = g.current_user
       db.session.add(post)
       db.session.commit()
       return jsonify(post.to_json()), 201, \
           {'Location': url_for('api.get_post', id=post.id)}

   @api.route('/posts/<int:id>', methods=['PUT'])
   @permission_required(Permission.WRITE)
   def edit_post(id):
       post = Post.query.get_or_404(id)
       if g.current_user != post.author and \
               not g.current_user.can(Permission.ADMIN):
           return forbidden('Insufficient permissions')
       post.body = request.json.get('body', post.body)
       db.session.add(post)
       db.session.commit()
       return jsonify(post.to_json())

   # app/api/decorators.py
   def permission_required(permission):
       def decorator(f):
           @wraps(f)
           def decorated_function(*args, **kwargs):
               if not g.current_user.can(permission):
                   return forbidden('Insufficient permissions')
               return f(*args, **kwargs)
           return decorated_function
       return decorator
   ```

10. Pagination of large resource collections:
    ```
    @api.route('/posts/')
    def get_posts():
        page = request.args.get('page', 1, type=int)
        pagination = Post.query.paginate(
            page, per_page=current_app.config['FLASKY_POSTS_PER_PAGE'],
            error_out=False)
        posts = pagination.items
        prev = None
        if pagination.has_prev:
            prev = url_for('api.get_posts', page=page-1)
        next = None
        if pagination.has_next:
            next = url_for('api.get_posts', page=page+1)
        return jsonify({
            'posts': [post.to_json() for post in posts],
            'prev_url': prev,
            'next_url': next,
            'count': pagination.total
        })
    ```
