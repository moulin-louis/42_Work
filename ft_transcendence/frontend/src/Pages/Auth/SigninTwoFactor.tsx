import { useEffect, useState } from "react";
import { User, useAuth } from "../../Context/AuthContext";

function SigninTwoFactor() {
  const [code, setCode] = useState('');
  const [token, setToken] = useState('');
  const { updateCurrentUser, setUser, setAccessToken } = useAuth();
  const [currentUser, setCurrentUser] = useState<User | null>(null);

  useEffect(() => {
    const cookies = document.cookie.split(';');
    let token = null;
    for (let i = 0; i < cookies.length; i++) {
      const cookie = cookies[i].trim();
      if (cookie.startsWith('Temporary=')) {
        token = cookie.split('=')[1];
        console.log("Temporary ", token);
        break;
      }
    }
    if (token) {
      const fetchUserData = async (token: string) => {
        try {
          const userData = await updateCurrentUser(token);
          console.log(typeof userData);
          console.log("user setToken ", userData);
          if (userData) {
            setCurrentUser(userData);
          }
        } catch (error) {
          console.log(error);
        }
      };
      fetchUserData(token);
      setToken(token);
    }
  }, []);

  useEffect(() => {
    console.log("CurrentUser:", currentUser);
  }, [] );

  const handleSubmit = async (e: React.FormEvent): Promise<void> => {
    e.preventDefault();
    console.log("handle submit");
    console.log("user ", currentUser);
    if (currentUser) {
      console.log("there is a user");
      try {
        const response = await fetch('http://localhost:3000/2fa/validate', {
          method: 'POST',
          body: JSON.stringify({ id: currentUser.id, code }),
          headers: {
            'Content-Type': 'application/json',
            Authorization: `Bearer ${token}`,
          },
          credentials: 'include',
        });
        if (response.ok) {
            console.log("response", response);
            setCurrentUser(null);
            // const cookies = response.headers.get('Set-Cookie');
            // if (cookies) {
            //   const parsedCookies = cookies.split(',');
            //   parsedCookies.forEach(cookie => {
            //     document.cookie = cookie;
            //   });
            // }
          
            // Redirect to the desired location
            window.location.href = 'http://localhost:4000/';
          } else {
            // Handle other response statuses or errors
            console.log('Validation failed:', response.statusText);
          }      } catch (error) {
        // Handle any errors here
      }
    }
  };

  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Go on your Auth app</h4>
      <form onSubmit={handleSubmit}>
        <div className="chat-full-width">
          <div className="chat-popup-head chat-popup-top-margin">Enter the code here:</div>
          <input
            type="number"
            value={code}
            className="chat-popup-input-text"
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
