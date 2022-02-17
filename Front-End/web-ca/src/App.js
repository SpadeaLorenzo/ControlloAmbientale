import logo from './logo.svg';
import './App.css';

import { BrowserRouter as Router, Route, Routes} from 'react-router-dom';

//Navbar
import Navbar from './Components/Navbar';

//Navbar pages
import Home from './pages/index';
import Fishino from './pages/fishino';
import Login from './pages/login';

//debug tool
import LogRocket from 'logrocket';
LogRocket.init('k8vuf7/controllo-ambientale');

function App() {
  return (
      <Router>
        <Navbar>
            <Route exact path="/" element={Home} />
            <Route exact path="/fishino" element={Fishino} />
            <Route exact path='/login' element={Login} />
        </Navbar>
    </Router>
  );
}

export default App;
