import os
from flask import Flask
from flask import request, redirect,url_for, render_template, session, flash
from flask_bootstrap import Bootstrap
from flask_wtf import FlaskForm
from flask_sqlalchemy import SQLAlchemy
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired
app = Flask(__name__)
app.config['SECRET_KEY'] = "finalkamehameha"
basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABSE_URI'] = "sqlite:///" + os.path.join(basedir, 'data.sqlite')
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
bootstrap = Bootstrap(app)
db = SQLAlchemy(app)

class NameForm(FlaskForm):
    name = StringField("What is your name", validators=[DataRequired()])
    submit = SubmitField('Submit')

@app.route('/')
def index():
    user_agent = request.headers.get('User-Agent')
    return '<h1>Sup{}!!</h1>'.format(user_agent)

@app.route('/index', methods=['GET','POST'])
def indexHtml():
    form = NameForm()
    name = None
    if form.validate_on_submit():
        old_name = session.get('name')
        if old_name and old_name != form.name.data:
            flash('you changed your name bro!')
        session['name'] = form.name.data
        return redirect(url_for('indexHtml'))
    return render_template('index.html', name=session.get('name'), form=form)
    

@app.route('/open/<name>')
def user(name):
    return redirect('https://www.{}.com'.format(name))

if __name__ == "__main__":
    app.run(host="0.0.0.0",port=5000,debug=True)