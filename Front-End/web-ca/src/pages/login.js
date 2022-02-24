import React from 'react';

import LoginInputs from '../Components/Login';


const Login = () => {
    return (
        <div style={{
            display: 'flex',
            justifyContent:'center',
            alignItems:'center',
            height: '100vh'
        }}>
            <h1>Login</h1>
            <LoginInputs/>
        </div>

    );
};

export default Login;