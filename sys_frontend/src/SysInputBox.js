import { useState } from "react";
// import { useHistory } from "react-router-dom";

function SysInputBox(props) {

    const [name, setName] = useState('');
    const [email, setEmail] = useState('');
    const [event, setEvent] = useState('1');
    const [seat, setSeat] = useState('1');
    const [result, setRestult] = useState('9');
    // const history = useHistory();
  
    const handleSubmit = (e) => {
      e.preventDefault();
      const blog = { name, email, event, seat, result };
      console.log(blog);
      const resource = name + "/" + email + "/" + event + "/" + seat;
      const url = new URL(resource, 'http://127.0.0.1:8080');

      fetch(url)
      .then((response) => response.json())
      .then((data) => {
        console.log('Success:', data);
      })
      .catch((error) => {
        console.error('Error:', error);
      });
    }
  
    return (
      <div className="create">
        <h2>Book an Event</h2>
        <form onSubmit={handleSubmit}>
          <label>Your Name:</label>
          <input 
            type="text" 
            required 
            value={name}
            onChange={(e) => setName(e.target.value)}
          />
          <label>Your E-mail:</label>
          <input 
            type="text"
            required
            value={email}
            onChange={(e) => setEmail(e.target.value)}
          ></input>
          <label>Choose an Event:</label>
          <select
            value={event}
            onChange={(e) => setEvent(e.target.value)}
          >
            <option value="1">21 Dec Movie Night - The Dark Knight</option>
            <option value="2">22 Dec New Friend Meet Up - Fight Club</option>
            <option value="3">23 Dec Costume Party - Titanic</option>
          </select>
          <label>Choose Seats:</label>
          <select
            value={seat}
            onChange={(e) => setSeat(e.target.value)}
          >
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
            <option value="4">4</option>
            <option value="5">5</option>
          </select>
          <button>Submit</button>
        </form>
      </div>
    );
}

export default SysInputBox;