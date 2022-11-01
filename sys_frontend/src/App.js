import React from 'react';
import './App.css';
// import Calculator from './Calculator'
// import CalculatorApi from './CalculatorApi'
import SysInputBox from './SysInputBox'

function App() {
  return (
    <div className="App">
      <header className="content">
        {/* <Calculator calculatorApi={new CalculatorApi('http://127.0.0.1:8080')} /> */}
        <SysInputBox />
      </header>
    </div>
  );
}

export default App;