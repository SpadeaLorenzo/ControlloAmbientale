const express = require("express")
const router = express.Router();
const Data = require("../models/data");

//creating data set 
router.post("/:id", async (req,res) =>{
    try {
        const datas = new Data({
            humidity: req.body.humidity,
            sound: req.body.sound,
            brightness: req.body.brightness,
            c02: req.body.c02,
            temperature: req.body.temperature,
            name : req.body.name,
        });

        const data = await datas.save();
        res.status(200).json(data);
    } catch (err) {
        res.status(500).json("Internal error " + err);
    }
});



router.delete("/:name", async (req, res) => {
        try {
            await Data.findByIdAndDelete(req.params.id);
            res.status(200).json("Data's been delated");
        }catch (err) {
            return res.status(500).json(err);
        }
        return res.status(403).json("stfu")
});



module.exports = router;