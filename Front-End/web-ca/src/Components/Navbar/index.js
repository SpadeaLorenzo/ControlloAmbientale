import React from 'react';
import{ 
    Nav,
    NavLink,
    Bars,
    NavMenu,
    NavBtn,
    NavBtnLink,
} from './NavbarElements';

const Navbar = () => {
    return (
        <>
            <Nav>
                <NavLink  style={{color: 'white', fontSize:35}} to='/'>
                <img src={require('../../Assets/favicon.ico')}></img>
                </NavLink>
                <NavMenu>
                    <NavLink to='/fishino'>
                        Fishino
                    </NavLink>
                    <NavLink to='/login'>
                        Login
                    </NavLink>
                </NavMenu>
            </Nav>
        </>
    );
};

export default Navbar;