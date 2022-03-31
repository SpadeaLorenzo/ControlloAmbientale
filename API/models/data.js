const mongoose = require("mongoose");

const dataSchema = mongoose.Schema({
    humidity:{
        type: String,
        required: true
    },
    sound:{
        type: String,
        required: true
    },
    brightness:{
        type: String,
        required: true,
    },
    c02:{
        type: String,
        required: true,
    },
    temperature:{
        type: String,
        required: true,
    },
    name:{
        type: String,
        required: true,
    },
},
{timestamps:true}
);

module.exports  = mongoose.model('Data' , dataSchema)