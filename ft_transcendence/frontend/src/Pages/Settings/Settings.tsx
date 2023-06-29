import React, { Dispatch, useEffect, useMemo, useRef, useContext, useState } from 'react';
import './../../index.css';
import './Settings.css';
import Header from '../../Navigation/Header/Header';
import Sidebar from '../../Navigation/Sidebar/Sidebar';

import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';

import 'react-circular-progressbar/dist/styles.css';

import AvatarImg from "./../../Images/Avatar.jpg";
import EditIcon from './icons/edit.svg';

import OverlayTrigger from 'react-bootstrap/OverlayTrigger';
import Tooltip from 'react-bootstrap/Tooltip';
import AlertIcon from './../../Images/Alert.svg';
import { useAuth } from '../../Context/AuthContext';
import { WebSocketContext } from '../../Context/WebSocketContext';
import { Socket } from 'socket.io-client';
import { set } from 'lodash';
import Resizer from 'react-image-file-resizer'

export interface TwoFactorAuthProps {
  checkboxValue: boolean;
  qrCode: string;
  secret: string;
  setCheckboxValue: Dispatch<React.SetStateAction<boolean>>;
  setQrCode: Dispatch<React.SetStateAction<string>>;
  setSecret: Dispatch<React.SetStateAction<string>>;
}



const InstructionsGoogle = React.forwardRef(function Dialog({}, ref) {
  return (
    <div>
      <div>Dialog content....</div>
    </div>
  )
})

function GoogleInfo() {
  return (
    <>
      <OverlayTrigger
        key={'left'}
        placement={'left'}
        overlay={
          <Tooltip id={`tooltip-${'left'}`}>
            <div style={{ textAlign: "left" }}>
              1) Open Google Auth App.<br></br>
              2) Scan the QR code.<br></br>
              3) Enter a 6-digit code.
            </div>
          </Tooltip>
        }
      >
        <div className="right"><img
          alt=""
          src={AlertIcon}
          width="30"
          height="30"
          className="alert-icon-margin"
          id="navbarScrollingDropdown"
        /></div>
      </OverlayTrigger>
    </>
  );
}



function QrImage({ qrCode }: { qrCode: string }) {
  return (
    <div>
      {qrCode && (
        <img
          alt=""
          src={qrCode}
          width="115"
          height="115"
          className="margin-circle"
          id="navbarScrollingDropdown"
        />
      )}
    </div>
  );
}

function QrImageContainer({ checkboxValue, qrCode, setCheckboxValue, setQrCode, secret, setSecret }: TwoFactorAuthProps) {
  const { user, accessToken } = useAuth();
  const hostname = useMemo(() => window.location.hostname, []);

  async function generateQrIcon() {
    try {
      const response = await fetch(`http://${hostname}:3000/2fa/generate`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${accessToken}` // Assuming you have an access token in the user object
        },
        body: JSON.stringify({ username: user?.username }),
        credentials: 'include',
      });
      const qrCode = await response.text();
      setQrCode(qrCode);
      localStorage.setItem('enable', 'true');
      localStorage.setItem('qrCode', qrCode);
      setCheckboxValue(true);

    } catch (error) {
    }
  }

  async function desactivateTwoFactorAuth() {
    try {
      const response = await fetch(`http://${hostname}:3000/2fa/desactivate`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${accessToken}` // Assuming you have an access token in the user object
        },
        body: JSON.stringify({ username: user?.username }),
        credentials: 'include',
      });
      setQrCode('');
      localStorage.setItem('enable', 'false');
      localStorage.setItem('qrCode', '');
      setCheckboxValue(false);


    } catch (error) {
    }

  }
  useEffect(() => {
    const fetchData = async () => {
      if (checkboxValue === true) {
        await generateQrIcon();
      }
      else {
        await desactivateTwoFactorAuth();
      }
    };

    fetchData();
  }, [checkboxValue]);

  return (
    <div>
      <QrImage qrCode={qrCode} />
    </div>
  );
}


function HeadingPage() {
  return (
    <Col xl={12}>
      <div className='inline'>
        <div className="left"><h1 className="heading heading-margin">Settings</h1></div>
      </div>
    </Col>

  )
}

let isOnline = true

function MainSettings() {
  const { user } = useAuth();
  const [username, setUsername] = useState<string>('');
  const [avatar, setAvatar] = useState({});
  const [uploadedImage, setUploadedImage] = useState<string | null>(null);
  const [login, setLogin] = useState<string>('');
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const inputRef = useRef<HTMLInputElement>(null);

  useEffect(() => {
    if (user) {
      setUsername(user.username);
      setLogin(user.login);
      if (user.avatar) {
        setUploadedImage(user.avatar);
      }
    }
  }, [user]);

  const handleReset = () => {
    if (user) {
      setUsername(user.username);
    }
  }

  const handleAvatar = (e: React.ChangeEvent<HTMLInputElement>) => {
    e.preventDefault();
    const file = e.target.files ? e.target.files[0] : null;
    if (file) {
      Resizer.imageFileResizer(
        file,
        800,
        800,
        'JPEG',
        100,
        0,
        (uri) => {
          setUploadedImage(uri as string);
          socket?.emit('updateavatar', {
            userId: user?.id,
            dataUrl: uri,
          });
        },
        'base64',
        200,
        200
      );
    }
  };


  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (user) {
      socket?.emit("updateusername", {
        userId: user.id,
        username,
      })
    }
  }

  return (
    <>
      <Col xl={6} className="margin-card" style={{ marginBottom: "30px" }}>
        <div className='card-settings inline-settings auth-shadow'>
          <div className='left'>
            <div className="heading-settings heading-settings-profile">
              Profile
            </div>
            <form onSubmit={handleSubmit}>
              <div className='profile-inline'>
                <div className='margin-img margin-mob'>
                  <div className="boost-achievements">
                    <div className="flex-friend items-center">
                      <Col lg={12} xl={3} className="padding-zero img-container-settings">
                        <img
                          alt=""
                          src={uploadedImage ?? AvatarImg}
                          width="160"
                          height="160"
                          className="avatar-border d-inline-block align-top"
                          id="navbarScrollingDropdown"
                        />
                        <input
                          ref={inputRef}
                          type="file"
                          onChange={handleAvatar}
                          accept="image/*"
                          style={{ display: 'none' }} />
                        <button
                          className="edit-img"
                          type="button"
                          onClick={() => inputRef.current?.click()}>
                          <img
                            alt=""
                            src={EditIcon}
                            width="10"
                            height="10"
                            className="d-inline-block edit-img-icon" />
                        </button>
                      </Col>
                    </div>
                  </div>
                </div>
                <div className='width-inputs full-width-mob'>
                  <div className="chat-full-width">
                    <div className="chat-popup-head margin-profile-head">Username PingPong</div>
                    <input
                      type="text"
                      className="chat-popup-input-text"
                      value={username}
                      onChange={(event) => setUsername(event.target.value)} />
                  </div>
                  {login && (
                    <div className="chat-full-width settings-margin-input">
                      <div className="chat-popup-head settings-margin-heading-input">Username 42</div>
                      <input
                        type="text"
                        value={login}
                        onChange={(event) => setLogin(event.target.value)}
                        className="chat-popup-input-text disable-input"
                      />
                    </div>
                  )}
                </div>
              </div>
              <div style={{ marginTop: "45px", display: "flex" }} className="align-settings-mob">
                <button className="chat-popup-button-blue full-width-mob buttons-settings-mob" type="submit">
                  Save changes
                </button>
                <button className="chat-popup-button-white full-width-mob buttons-settings-mob" type="button" onClick={handleReset}>
                  Reset to default
                </button>
              </div>
            </form>
          </div>
        </div>
      </Col>
    </>
  )
}

function SecuritySettings() {
  const [checkboxClass, setCheckboxClass] = useState<string>("chat-popup-checkbox");
  const hostname = useMemo(() => (window.location.hostname), []);
  const { user, updateCurrentUser, accessToken } = useAuth();
  const [checkboxValue, setCheckboxValue] = useState(() => {
    const storedValue = localStorage.getItem('enable');
    return storedValue === 'true';
  });
  const [qrCode, setQrCode] = useState('');
  const [secret, setSecret] = useState('');
  const [errorState, setErrorState] = useState('');
  const [fieldStyle, setFieldStyle] = useState('');
  const [messageStyle, setMessageStyle] = useState('');
  const [twoFAActivated, setTwoFAActivated] = useState(false);

  useEffect(() => {
    async function fetchUser2FA() {
      if (accessToken) {
        try {
          await updateCurrentUser(accessToken);
        } catch (error) { }
      }
      if (user?.authEnable) {
        setCheckboxValue(true);
        setTwoFAActivated(true);
        localStorage.setItem('enable', 'true');
      } else {
        localStorage.setItem('enable', 'false');
        setCheckboxValue(false);
      }
    }
    fetchUser2FA();
  }, [accessToken, updateCurrentUser, user]);



  const activateTwoFactorAuth = async (code: string) => {
    if (user) {

      try {
        const id = user.id;
        const response = await fetch(`http://${hostname}:3000/2fa/activate`, {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${accessToken}`
          },
          body: JSON.stringify({ twoFactorAuthenticationCode: secret, id: id }),
          credentials: 'include',
        });
        const message = await response.json();
        if (response.ok) {
          setErrorState(message.message || 'You have activated the two factors authentication');
          setFieldStyle(message.message ? 'success-border' : '');
          setMessageStyle(message.message ? 'notify-auth-success' : '');
          setTwoFAActivated(true);
        } else {
          setErrorState(message.error || 'Your code is expired or not valid');
          setFieldStyle(message.error ? 'error-border' : '');
          setMessageStyle(message.error ? 'notify-auth-error' : '');

        }
      } catch (error) {
      }
    }

  };



  return (
    <>
      <Col xl={6} className="margin-card" style={{ marginBottom: "30px" }}>
        <div className='card-settings inline-settings auth-shadow'>
          <div className='left'>
            <div className="heading-settings full-width">
              <div>Google Authenticator</div>
              <div className='margin-circle'>
                {GoogleInfo()}
              </div>
            </div>
            <div className='box-with-icon full-width align-settings-mob'>
              <div className='width-inputs full-width-mob'>
                <div className="chat-full-width">
                  <div className="settings-margin-google-input chat-popup-head">Click to connect 2-factor authorization</div>
                  <div className={checkboxClass} onClick={() => {
                    setCheckboxValue(prevState => !prevState);
                    setTwoFAActivated(false);
                    setErrorState('');
                    setFieldStyle('');
                    setMessageStyle('');
                    setSecret('');
                    checkboxClass === "chat-popup-checkbox"
                      ? setCheckboxClass("chat-popup-checkbox-changed")
                      : setCheckboxClass("chat-popup-checkbox");
                  }}>
                    <input
                      type="checkbox"
                      checked={checkboxValue}
                      onChange={() => {}}
                      style={{ marginRight: "15px" }}
                    />
                    Enable Google Auth
                  </div>
                </div>
              </div>
              {!twoFAActivated && <div className='margin-circle full-width-mob margin-mob qr-margin'>
                <div className="">
                  <div className="flex-friend items-center">
                    <Col lg={12} xl={3} className="padding-zero img-container-settings">
                      <QrImageContainer
                        checkboxValue={checkboxValue}
                        qrCode={qrCode}
                        secret={secret}
                        setCheckboxValue={setCheckboxValue}
                        setQrCode={setQrCode}
                        setSecret={setSecret}
                      />
                    </Col>
                  </div>
                </div>
              </div>}
            </div>
            {qrCode && !twoFAActivated && (
              <div className="chat-full-width">
                <div className="chat-popup-head chat-popup-top-margin">Verification code</div>
                <input
                  type="number"
                  maxLength={6}
                  value={secret}
                  className={`chat-popup-input-text ${fieldStyle}`}
                  onChange={(e) => setSecret(e.target.value)}
                />
                <div style={{ marginTop: "26px", display: "flex" }} className="align-settings-mob">
                  <button onClick={() => activateTwoFactorAuth(secret)} className="chat-popup-button-blue full-width-mob buttons-settings-mob" type="submit">
                    Send Code
                  </button>
                </div>
              </div>

            )}
            {errorState && <div className={`${messageStyle}`}>{errorState}</div>}
          </div>
        </div>
      </Col>
    </>
  )
}

function PasswordSettings() {
  const [password, setPassword] = useState<string>("");
  const [confirmPassword, setConfirmPassword] = useState<string>("");

  const socket = useContext<Socket | undefined>(WebSocketContext);
  const { user } = useAuth();

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (user) {
      socket?.emit("updatepassword", {
        userId: user.id,
        password,
        confirmPassword,
      });
    }
    setPassword("");
    setConfirmPassword("");
  }


  return (
    <>
      {!user?.login && (
        <Col xl={6} className="margin-card" style={{ marginBottom: "30px" }}>
          <div className='card-settings inline inline-achievements auth-shadow'>
            <div className='left full-width'>
              <div className="heading-settings">
                Change password
              </div>
              <form onSubmit={handleSubmit}>
                <div className="chat-full-width">
                  <div className="chat-popup-head chat-popup-top-margin">Password</div>
                  <input
                    type="password"
                    value={password}
                    className="chat-popup-input-text"
                    onChange={(e) => setPassword(e.target.value)}
                  />
                </div>
                <div className="chat-full-width">
                  <div className="chat-popup-head chat-popup-top-margin">Confirm password</div>
                  <input
                    type="password"
                    value={confirmPassword}
                    className="chat-popup-input-text"
                    onChange={(e) => setConfirmPassword(e.target.value)}
                  />
                </div>
                <div className='chat-full-width' style={{ marginTop: "25px", display: "flex" }}>
                  <button className="chat-popup-button-blue full-width text-in-center buttons-settings-mob" type="submit">
                    Change password
                  </button>
                </div>
              </form>
            </div>
          </div>
        </Col>
      )}
    </>
  )
}

function Body() {


  return (
    <Container>
      <Row className="zero-margin">
        <Col lg={12} xl={2} className="sidebar-global">
          <Sidebar />
        </Col>
        <Col lg={12} xl={10}>
          <div className="content">
            <Row>
              <HeadingPage />
              <MainSettings />
              <PasswordSettings />
              <SecuritySettings />
            </Row>
          </div>
        </Col>
      </Row>
    </Container>
  );
}

function Settings() {
  return (
    <>
      <Header />
      <Body />
    </>
  );
}

export default Settings;
