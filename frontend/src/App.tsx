import React from 'react';
import HomePage from './pages/HomePage';
import 'bootstrap/dist/css/bootstrap.min.css';

const App: React.FC = () => {
  return (
    <div className="App container py-5">
      <header className="App-header px-2">
        <h1>Spatial Index</h1>
      </header>
      <HomePage />
    </div>
  );
};

export default App;
