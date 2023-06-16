import { useMemo, useState } from "react";

const Signin: React.FC = () => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [errorState, setErrorState] = useState({ username: '', password: '' });
  const [fieldStyle, setFieldStyle] = useState({ username: '', password: '' });
  const hostname = useMemo(() => (window.location.hostname), []);

  const handleSubmit = async (e: any) => {
    e.preventDefault();
    let errors = { username: '', password: '' };

    if (!username) {
      errors.username = 'Username should not be empty';
    }

    if (!password) {
      errors.password = 'Password should not be empty';
    }

    if (errors.username || errors.password) {
      setErrorState(errors);
      setFieldStyle({
        username: errors.username ? 'error-border' : '',
        password: errors.password ? 'error-border' : '',
      });
      return;
    }

    try {
      const response = await fetch(`http://${hostname}:3000/auth/signin`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username, password }),
        credentials: 'include', // Include credentials for cross-origin requests
      });
      if (response.ok) {
        const data = await response.json();
        console.log(data);
        window.location.href = data.redirectUrl;      }
      else {
        const errorData = await response.json();
        setErrorState({ username: errorData.message, password: errorData.message });
        setFieldStyle({
          username: errorData.message ? 'error-border' : '',
          password: errorData.message ? 'error-border' : '',
        });
        return;
      }
    } catch (error) {
      console.error('Signup error:', error);
    }
  };

  return (
    <div>
      <form onSubmit={handleSubmit}>
        <div className="chat-full-width">
          <div className="chat-popup-head auth-head-top-margin">
            Username
          </div>
          <input
            type="text"
            className={`chat-popup-input-text ${fieldStyle.username}`}
            placeholder="Username"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
          />
          {errorState.username && <div className="notify-auth-error">{errorState.username}</div>}
        </div>
        <div className="chat-full-width">
          <div className="chat-popup-head auth-head-top-margin">
            Password
          </div>
          <input
            type="password"
            placeholder="Password"
            value={password}
            className={`chat-popup-input-text ${fieldStyle.password}`}
            onChange={(e) => setPassword(e.target.value)} />
          {errorState.password && <div className="notify-auth-error">{errorState.password}</div>}
        </div>
        <div style={{ marginTop: "30px", display: "flex" }}>
          <button type="submit" className="chat-popup-button-blue">Login</button>
        </div>
      </form>
    </div>
  );
};

export default Signin;
