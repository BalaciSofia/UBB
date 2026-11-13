class User{
    constructor({id, username, membershipType}){
        this.id = id;
        this.username = username;
        this.membershipType=membershipType;
    }
}

module.exports = User;