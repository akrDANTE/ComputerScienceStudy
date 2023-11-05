# Flask - Web Framework

Flask is a micro framework which provides barebones for web development and can be extended using extensions.\
Flask has three dependecies:

1. routing, debugging and Web Server Gateway interface(WSGI) => Werkzeug
2. Template support => Jinja2
3. command-line integration => Click.

## Basics

1. All flask applications must create and application instance. The webserver passes all requests it receives from clients to this object for handling, using a protocal called WSGI. application instance is an object of class Flask.
   The only required argument is name of the main module or package of the application.\
    from flask import Flask\
    app = Flask(\_\_name\_\_)\
   The \_\_name\_\_ argument tells flask the main directory of the app and where to find other files like templates.
2. Routes and view functions:\
   @app.route('route_address')\
   def route_function():\
   The line staring with @ is a python decorator. common use of decorators is to register functions as callbacks.
   Alternately following can also be used here:\
   app.add_url_rule('/', 'index', index)\
   Here return value of the index function is the response of the webserver to the client.\
   The address of the route can be used to pass parameters to the function as shown:\
   @app.route('/user/\<name>')\
   def user(name):\
    return 'hello, {}'.format(name)
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

6. app.url_map to view the available routes in the form of a hash-map.\
   Map([<Rule '/' (HEAD, OPTIONS, GET) -> index>,\
   <Rule '/static/<filename>' (HEAD, OPTIONS, GET) -> static>,\
   <Rule '/user/<name>' (HEAD, OPTIONS, GET) -> user>])
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
   return '\<h1>stuff\</h1>', response_code, headers\
   flask provides make_response function for returning responses. Example:\
   response = make_response('\<h1>test\<\h1>')\
   response.set_cookie('answer', '42')\
   return response\
   There is a special type of response called redirect which returns a new URL for the browser to navigate to, indicated by 302 status code.\
   from flask import redirect

## Templates

Seperates the business logic and the presentation logic. Templates contains the response text with placeholders for dynamic stuff, which are provided by the request handler or view function.

1. Jinja2 template engine\
   {{ name|capitalize }} #capitalize filter.
   other filters available, safe, lower, upper, title, trip, striptags.
   https://jinja.palletsprojects.com/en/3.1.x/templates/#builtin-filters

   {% if user %}\
    Hello {{ user }}!\
   {% else %}\
    Hello, stranger!\
   {% endif %}

   {% for comment in comments %}\
    \<li> {{ comment }} \</li>\
   {% endfor %}

   macros: are like functions in python.\
   {% macro render_comment(comment) %}\
    \<li> {{ comment }} \</li>\
   {% end_macro %}

   then can be rendered like {{ render_comment(comment) }}

   Macros can be written to a seperate file and can be imported later.\
   {% import 'macros.html' as macros %} which can be then used as\
   {{ macros.render_comment(comment) }}

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

2. Form Classes: each form is represented by a class that inherits from the class FlaskForm. This contains lists of fields in the form as objects and each of these objects can have validators attached.\
   from flask_wtf import FlaskForm\
   from wtforms import StringField, SubmitField\
   from wtforms.validators import DataRequired\
   class NameForm(FlaskForm):\
   name = StringField('What is your Name?', validators=[DataRequired()])\
   submit = SubmitField('Submit')\
   following fields are available: BooleanField, DateField, DateTimeField, DecimalField, FileField, HiddenField, MultipleFileField, FieldList, FloatField,
   FormField, IntegerField, PasswordField, RadioField, SelectField, SelectMultipleField, SubmitField, StringField, TextAreaField\
   Following validators are available: DataRequired, Email, EqualTo, InputRequired,IPAddress, Lenght, MacAddress, NumberRange, Optional, Regexp, URL, UUID, AnyOf, NoneOf\

3. The forms generated using above can be rendered as HTML as shown:\
   \<form>\
   &nbsp; &nbsp; {{ form.hidden_tag() }}\
   &nbsp; &nbsp; {{ form.name.label }} {{ form.name(id='my-text-field') }}\
   &nbsp; &nbsp; {{ form.submit() }}\
   \</form>\
   Another way is to use the bootstrap like so:\
   {% import "bootstrap/wtf.html" as wtf %}
   {{  wtf.quick_form(form) }}

4. Form Handling in view functions.\
   name = None\
   form = NameForm()\
   if form.validate_on_submit():\
   &nbsp; &nbsp; name = form.name.data
   &nbsp; &nbsp; form.name.data = ''
   return render_template('index.html', form=form, name=name)

5. As during form submit, the page refreshes the request is sent to the server for handling. Then response is returned to the client. But when client refreshes the page, same post request is repeated by the client's browser, which is not desirable. To handle this response is returned using redirect.\
   Also when redirecting the data received from the form will be lost, that data can be stored in the user sessions.\
   if form.validate_on_submit():\
    &nbsp; &nbsp; session['name'] = form.name.data\
   &nbsp; &nbsp; return redirect(url_for('index'))
   return render_template('index.html', form=form, name=session.get('name'))

6. Message Flashing: the flash displays a message to the user based on the handling of the form.\
   flash('Looks like you have changed your name!')\
   these messages are displayed in templates using:\
   {% for message in get_flashed_messages() %}\
   \<div class="alert alert-warning">\
   \<button type="button" class="close" data-dismiss="alert">&times;\</button>\
   {{ message }}\
   \</div>

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
