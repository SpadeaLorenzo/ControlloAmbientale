const mongoose = require ("mongoose");

const userSchema = mongoose.Schema({
    username:{
        type:String,
        require: true,
        min:6,
        max:20,
        unique: true
    },

    email : {
        type:String,
        required:true,
        min:6
    },

    password:{
        type:String,
        require:true,
        min: 8
    },

    isAdmin:{
        type: Boolean,
        default: true
    },
},
{timestamps:true}
);
module.exports  = mongoose.model('User' , userSchema)