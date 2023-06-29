import _ from "lodash";
import React, { useContext, useState, useEffect } from "react";
import { Socket } from "socket.io-client";
import { Channel, ChannelContext } from "../../Context/ChannelContext";
import { WebSocketContext } from "../../Context/WebSocketContext";
import LockIcon from "./../../Images/Lock.svg";
import { useAuth } from "../../Context/AuthContext";

/**
 * The `ChannelJoin` component provides an interface for a user to join a new channel.
 * The user can only join channels they are not already members of and are not banned from.
 *
 * @param onClose - A function to close the join channel form.
 * @returns A React element.
 */

function ChannelJoin({ onClose }: { onClose: () => void }): React.JSX.Element {
  const [checkPassword, setCheckPassword] = useState<
    { onClose: () => void; userId: string; channel: Channel } | undefined
  >();
  const socket = useContext<Socket | undefined>(WebSocketContext);
  const allChannels = useContext(ChannelContext);
  const { user } = useAuth();

  const channelsJoinable = _(allChannels)
    .filter(
      (channel) => !channel.members?.includes(user?.id ?? "") && !channel.secret
    )
    .value();

  const handleJoin = (channel: Channel) => {
    if (channel.protected) {
      setCheckPassword({ onClose, userId: user?.id ?? "", channel });
      return;
    }

    socket?.emit("joinchannel", {
      userId: user?.id ?? "",
      channelId: channel.id,
    });

    onClose();
  };

  return (
    <div className="chat-popup-window">
      <h4 className="chat-popup-big-head">Join channel</h4>
      {!checkPassword && (
        <div>
          {channelsJoinable.map((c) => (
            <div className="chat-popup-inline" key={c.id}>
              <div className="margin-right-popup">#{c.name}</div>
              {c.protected && (
                <img alt="" src={LockIcon} width="20" height="20" />
              )}
              <div className="chat-popup-button-margin">
                <button
                  className="chat-popup-small-button"
                  onClick={() => handleJoin(c)}
                >
                  Join
                </button>
              </div>
            </div>
          ))}
        </div>
      )}
      {checkPassword && <CheckPassword {...checkPassword} />}
      {!checkPassword && (
        <div style={{ marginTop: "45px", display: "flex" }}>
          <button
            className="chat-popup-button-white"
            type="button"
            onClick={onClose}
          >
            Cancel
          </button>
        </div>
      )}
    </div>
  );
}

/**
 * The `CheckPassword` component provides an interface for a user to enter a password for a protected channel.
 * If the password is correct, the user joins the channel. If not, or if the password check doesn't respond within 1 second, an error message is displayed.
 *
 * @param onClose - A function to close the password input form.
 * @param userId - The id of the user trying to join the channel.
 * @param channel - The channel that the user is trying to join.
 * @returns A React element.
 */
function CheckPassword({
  onClose,
  userId,
  channel,
}: {
  onClose: () => void;
  userId: string;
  channel: Channel;
}): React.JSX.Element {
  const [password, setPassword] = useState<string>("");
  const [incorrect, setIncorrect] = useState<boolean>(false);
  const socket = useContext<Socket | undefined>(WebSocketContext);

  const handleAdd = () => {
    const timerId = setTimeout(() => {
      setIncorrect(true);
    }, 1000);

    socket?.on("checkchannelpassword", (isCorrect) => {
      clearTimeout(timerId);
      if (isCorrect) {
        socket?.emit("joinchannel", { userId, channelId: channel.id });
        onClose();
      } else {
        setIncorrect(true);
      }
    });

    socket?.emit("checkchannelpassword", {
      id: channel.id,
      password,
    });
  };

  useEffect(() => {
    return () => {
      socket?.off("checkchannelpassword");
    };
  }, [socket]);

  return (
    <>
      <div className="chat-popup-head chat-popup-top-margin">Password:</div>
      <input
        type="password"
        value={password}
        className="chat-popup-input-text"
        onChange={(e) => setPassword(e.target.value)}
        placeholder="Enter password"
      />
      {incorrect && <div className="notify-popup-error">Invalid Password</div>}
      <div className="margin-top-popup">
        <button
          className="chat-popup-small-join"
          type="button"
          onClick={handleAdd}
        >
          Join
        </button>
        <button
          className="chat-popup-small-cancel"
          type="button"
          onClick={onClose}
        >
          Cancel
        </button>
      </div>
    </>
  );
}

export default ChannelJoin;
