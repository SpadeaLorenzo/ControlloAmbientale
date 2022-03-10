

const express = require("express");
const dotenv = require("dotenv");
const mongoose = require("mongoose");
const morgan = require("morgan");
const helmet = require("helmet");


const dataRoute = require("./routes/data");
const userRoute = require("./routes/user");

dotenv.config();

const app = express();

mongoose.connect('mongodb://localhost:27017/Test_CA' , {useNewUrlParser: true}, ()=>{
    console.log("Database connected");
});



//middleware 
app.use(express.json());
app.use(helmet());
app.use(morgan("common"));


app.use("/ControlloAmbientale/data" , dataRoute);
app.use("/ControlloAmbientale/user", userRoute);

app.listen(8080 , ()=>{
    console.log("backend running on 8080");
});