import { useState } from "react";
// import { useHistory } from "react-router-dom";

function SysInputBox(props) {

    const [name, setName] = useState('');
    const [email, setEmail] = useState('');
    const [event, setEvent] = useState('1');
    const [result, setRestult] = useState('9');
    // const history = useHistory();
  
    const handleSubmit = (e) => {
      e.preventDefault();
      const blog = { name, email, event, result };
      console.log(blog);

      const resource = name + "/" + email + "/" + event;
      const url = new URL(resource, 'http://127.0.0.1:8080');

      fetch(url)
      .then((response) => response.json());
      // fetch(url, {
      //   method: 'POST',
      //   headers: { 
      //     // "credentials": "include",
      //     "Content-Type": "application/json",
      //     // "Access-Control-Allow-Origin": "*" 
      //   },
      //   body: JSON.stringify(blog)
      // })
      // .then((response) => response.json());
      // .then((data) => {
      //   console.log('Success:', data);
      // })
      // .catch((error) => {
      //   console.error('Error:', error);
      // });

      // fetch(url, {
      //   method: 'POST',
      //   headers: { "Content-Type": "application/json" },
      //   body: JSON.stringify(blog)
      // })
      // .then((response) => response.json())
      // .then((data) => {
      //   console.log('Success:', data);
      // })
      // .catch((error) => {
      //   console.error('Error:', error);
      // });
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
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
          </select>
          <button>Submit</button>
        </form>
      </div>
    );
}

export default SysInputBox;