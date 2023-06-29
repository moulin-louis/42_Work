import { useMemo } from 'react';
import Logo42 from './img/42.svg';

export interface IProps {
  changeForm: (formName: 'login' | 'signup' | 'signin') => void;
}

const Login: React.FC<IProps> = ({ changeForm }) => {
  const hostname = useMemo(() => (window.location.hostname), []);
  const handleOAuthClick = () => {
    const uid = process.env.REACT_APP_INTRA42_UID;
    const uri = `http://localhost:${process.env.REACT_APP_PORT}/auth/callback`;
    const url = `https://api.intra.42.fr/oauth/authorize?client_id=${uid}&redirect_uri=${uri}&response_type=code&scope=public`;
    window.location.href = url;
  }

  return (
    <>
      <button className="auth-button auth-margin auth-right-margin" onClick={handleOAuthClick}>
        <img className="auth-button-icon" src={Logo42} alt="" />
        <div className="auth-button-text">
          Login with Intra
        </div>
      </button>
      <button className="auth-guest-button" onClick={() => changeForm('signin')}>
        <div className="auth-button-guest-text">
          Classic login
        </div>
      </button>
    </>
  );
}

export default Login;
