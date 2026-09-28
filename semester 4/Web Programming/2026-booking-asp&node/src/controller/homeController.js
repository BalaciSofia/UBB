
const MainRepository =  require('../repository/mainRepository')
const User = require('../domain/user');
const Booking = require('../domain/booking');
const Class = require('../domain/class');
const Waitlist = require('../domain/waitlist');

class HomeController{
    constructor(){
        this.repository = new MainRepository();
        this.getClasses = this.getClasses.bind(this);
        this.bookClass = this.bookClass.bind(this);
        this.getUserBookings = this.getUserBookings.bind(this);
        this.cancelBooking = this.cancelBooking.bind(this);
    }

    async getClasses(req,res){
        const {classes,available} = await this.repository.getUpcomingClasses();
        return res.json({ classes, available});
    }

    async bookClass(req,res){
        const classId= req.body.classId;
        const userId = req.session.user.id;
        const result = await this.repository.bookClass(userId,classId);
        return res.json(result);
    }

    async getUserBookings(req,res){
        const userId = req.session.user.id;
        const result = await this.repository.getUsersBookings(userId);
        return res.json(result);
    }

    async cancelBooking(req,res){
        const userId = req.session.user.id;
        const classId= req.body.classId;
        const bookingId = req.body.bookingId;
        const result = await this.repository.cancelBooking(bookingId,classId,userId);
        return res.json(result);
    }

}

module.exports = HomeController;