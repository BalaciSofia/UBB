class Booking{
    constructor({id,userID,classID,bookedAt,cancelled}){
        this.id=id;
        this.classID=classID;
        this.userID=userID;
        this.bookedAt=bookedAt;
        this.cancelled=cancelled;
    }
}

module.exports = Booking;