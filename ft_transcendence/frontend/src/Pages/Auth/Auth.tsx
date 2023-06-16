import React, { Component } from 'react';

import './Auth.css';

import Logo from './img/Logo.svg'
import UserImg from './img/Avatar.jpg'

import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import Login, { IProps as LoginProps } from './Login';
import Signin from './Signin';
import Signup from './Signup';

import Tabs from 'react-bootstrap/Tabs';
import Tab from 'react-bootstrap/Tab';


class TextAuth extends React.Component {
  render() {
    return <div className="auth-big-margin">
      <img className="auth-logo-center auth-small-margin" src={Logo} alt="" />
      <div className="auth-text-heading auth-text-center">
        Ping Pong Game <br />for Ecole42
      </div>
    </div>;
  }
}

class UsersInfo extends React.Component {
  render() {
    return <div className="col-start-3 col-span-4 flex-inline auth-vertical-center">
      <div className="auth-avatars-margin">
        <img className="auth-avatar-circle" src={UserImg} alt="" />
        <img className="auth-avatar-circle" src={UserImg} alt="" />
        <img className="auth-avatar-circle" src={UserImg} alt="" />
      </div>
      <div>
        10+ people joined us, now it’s your turn
      </div>
    </div>;
  }
}

function LeftAuth() {
  return (
    <div className="col-start-2 col-span-5 auth-text-center">
      <TextAuth />
      <UsersInfo />
    </div>
  );
}

class AuthDescription extends React.Component {
  render() {
    return <div className="auth-description">
      You must have an Intra 42 profile to be authorized. The connection is secure, with all data securely encrypted.
    </div>;
  }
}

interface IState {
  currentForm: 'login' | 'signin' | 'signup';
}

interface IProps { }

class RightAuth extends Component<IProps, IState> {
  constructor(props: IProps) {
    super(props);
    this.state = {
      currentForm: 'login' // login, signup, signin
    };
  }

  changeForm = (eventKey: string | null) => {
    if (eventKey) {
      this.setState({ currentForm: eventKey as 'login' | 'signin' | 'signup' });
    }
  }

  render() {
    const { currentForm } = this.state;

    return (
      <div className="col-span-4 auth-shadow bg-white auth-rounded-corners p-8 auth-padding">
        {currentForm !== 'login' && <button className="auth-small-button" onClick={() => this.changeForm('login')}>
          <div className="auth-small-button-text">← Return to all types</div>
        </button>}
        {currentForm === 'login' && <>
          <div className="auth-text-heading auth-margin">
            {currentForm.charAt(0).toUpperCase() + currentForm.slice(1)}
          </div>
          <Login changeForm={this.changeForm} />
          <AuthDescription />
        </>
        }
        {currentForm !== 'login' &&
          <Tabs defaultActiveKey="signin" onSelect={this.changeForm}>
            <Tab
              eventKey="signin"
              title="Login">
              <Signin />
            </Tab>
            <Tab
              eventKey="signup"
              title="Register"
            >
              <Signup />
            </Tab>
          </Tabs>
        }
        {/* <Logout /> */}
      </div>
    );
  }
}

function Body() {
  return (<Container className='content-auth'>
    <Row className="zero-margin items-center justify-center full-screen zero-margin-auth">
      <Col lg={12} xl={5} className='zero-margin zero-margin-auth'>
        <LeftAuth />
      </Col>
      <Col lg={12} xl={4} className='zero-margin zero-margin-auth login-block'>
        <RightAuth />
      </Col>
    </Row>
  </Container>)
}

function Auth() {
  return (
    <Body />
  );
}

export default Auth;