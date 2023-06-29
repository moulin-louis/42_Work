import { Link } from "react-router-dom";
import "./ErrorPage.css";
import ArrowLeft from "./../../Images/Arrow-Left.svg";
import Background from "./../../Images/BG.svg";

function ErrorPage() {
  return (
    <div
      id="error-page"
      className="error-background"
      style={{
        backgroundImage: `url(${process.env.REACT_APP_PUBLIC_URL + Background})`,
      }}
    >
      <div className="error-block">
        <div className="ball-container">
          <div className="ball ball-small"></div>
          <div className="ball ball-medium"></div>
          <div className="ball ball-large"></div>
        </div>
        <p className="error-title">404</p>
        <p>
          <i className="error-description">Page not found</i>
        </p>
        <Link to="/">
          <button className="AuthMargin error-button">
            <img className="error-button-icon" src={ArrowLeft} alt="" />
            <div className="error-button-text">Back to Home</div>
          </button>
        </Link>
      </div>
    </div>
  );
}

export default ErrorPage;
