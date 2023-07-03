import { useEffect, useState } from "react";
import { User, useAuth } from "../../Context/AuthContext";

function SigninTwoFactor() {
  const [code, setCode] = useState('');
  const [token, setToken] = useState('');
  const { updateCurrentUser, setUser, setAccessToken } = useAuth();
  const [currentUser, setCurrentUser] = useState<User | null>(null);
  const [errorState, setErrorState] = useState('');
  const [fieldStyle, setFieldStyle] = useState('');

  useEffect(() => {
    const cookies = document.cookie.split(';');
    let token = null;
    for (let i = 0; i < cookies.length; i++) {
      const cookie = cookies[i].trim();
      if (cookie.startsWith('Temporary=')) {
        token = cookie.split('=')[1];
        break;
      }
    }
    if (token) {
      const fetchUserData = async (token: string) => {
        try {
          const userData = await updateCurrentUser(token);
        } catch (error) {
        }
      };
      fetchUserData(token);
      setToken(token);
    }
  }, []);

  useEffect(() => {
  }, [] );

  const handleSubmit = async (e: React.FormEvent): Promise<void> => {
    e.preventDefault();

    if (currentUser) {
      try {
        const response = await fetch(`http://localhost:3000/2fa/validate`, {
          method: 'POST',
          body: JSON.stringify({ id: currentUser.id, code }),
          headers: {
            'Content-Type': 'application/json',
            Authorization: `Bearer ${token}`,
          },
          credentials: 'include',
        });

        if (response.ok) {
          setCurrentUser(null);
          window.location.href = `http://localhost:${process.env.REACT_APP_PORT}/settings`;
        } else {
          const errorData = await response.json();
          setErrorState(errorData.error || 'An error occurred');
          setFieldStyle(errorData.error ? 'error-border' : '');
        }
      } catch (error) {
      }
    }
};

return (
  <div className="chat-popup-window">
    <h4 className="chat-popup-big-head">Go on your Auth app</h4>
    <form onSubmit={handleSubmit}>
      <div className="chat-full-width">
        {errorState && <div className="notify-auth-error">{errorState}</div>}
        <div className="chat-popup-head chat-popup-top-margin">Enter the code here:</div>
        <input
          type="number"
          value={code}
          className={`chat-popup-input-text ${fieldStyle}`}
          onChange={(e) => setCode(e.target.value)}
        />
      </div>
      <div style={{ marginTop: "45px", display: "flex" }}>
        <button className="chat-popup-button-blue" type="submit">
          send code
        </button>
      </div>
    </form>
  </div>
);
}

export default SigninTwoFactor;
