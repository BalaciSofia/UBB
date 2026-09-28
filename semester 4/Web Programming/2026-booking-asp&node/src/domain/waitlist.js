class Waitlist{
    constructor({id,userID,classID,addedAt}){
        this.id=id;
        this.userID=userID;
        this.classID=classID;
        this.addedAt=addedAt;
    }
}

module.exports = Waitlist;