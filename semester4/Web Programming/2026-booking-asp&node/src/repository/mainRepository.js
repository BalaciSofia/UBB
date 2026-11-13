const pool = require('./config');
const User = require('../domain/user');
const Booking = require('../domain/booking');
const Class = require('../domain/class');
const Waitlist = require('../domain/waitlist');

class MainRepository {
    async authenticate(username, password) {
        const [rows] = await pool.execute(
            'SELECT * FROM users WHERE username = ?',
            [username]
        );
        if (rows.length === 0) {
            return null;
        }
        let a = new User(rows[0])
        return a;
    }

    async getActiveBookingsForClass(classID){
        const [rows] = await pool.execute(
            'SELECT count(*) as count FROM classes c inner join bookings b on c.id=b.classID' +
             ' WHERE b.cancelled=0 and c.id=?',[classID]
        );
        return rows[0].count;
    }

    async getUpcomingClasses(){
        const [rows] = await pool.execute(
            'SELECT * FROM classes WHERE classDate >= DATE(NOW())'
        );
        const classes=[];
        for(const r of rows){
            let c = new Class(r)
            classes.push(c);
        }
        const available=[];
        for(const c of classes){
            let max=c['maxCapacity'];
            available.push(max - await this.getActiveBookingsForClass(c['id']));
        }
        return {classes,available};
    }
    async getUserMembership(userID){
        const [rows] = await pool.execute(
            'SELECT membershipType FROM users WHERE id=?',[userID]
        );
        return rows[0].membershipType;
    }

    async isClassLow(classID){
        const [rows] = await pool.execute(
            'SELECT * FROM classes WHERE id=? and className like \'%Low\'',[classID]
        );
        if(rows.length === 0)return false;
        return true;
    }


    async bookClass(userId,classId){
        if(!await this.isClassLow(classId) && await this.getUserMembership(userId)=='basic'){
            return "High intensity classes are only available for premium members only";
        }
        else{
            const [rows1] = await pool.execute(
                'SELECT * FROM bookings WHERE userID=? and classID=? and cancelled=0',[userId,classId]
            );
            const [rows2] = await pool.execute(
                'SELECT * FROM waitlist WHERE userID=? and classID=?',[userId,classId]
            );
            if(rows1.length>0 || rows2.length>0){
                return "You already booked this class";
            }

            const [rows] = await pool.execute(
            'SELECT * FROM classes WHERE id=?',[classId]
            );
            const available = rows[0]['maxCapacity']-await this.getActiveBookingsForClass(classId);


            if (available<=0){
                //add to waitlist
                const date = new Date();
               const [result] = await pool.execute(
            'INSERT INTO waitlist (userID, classID,addedAt) VALUES (?, ?, ?)',
            [userId, classId, date]
        );
        return "you ve beed added to the waitlist";
            }else{
                //add booking
                const date = new Date();
               const [result] = await pool.execute(
            'INSERT INTO bookings (userID, classID, bookedAt, cancelled) VALUES (?, ?, ?, ?)',
            [userId, classId, date, 0]
        );
        if(await this.hasThreeOrMoreBookings(userId)){
            if(await this.hasAllBookingTheSame(userId)){
                return "booking sucessfull"+"all your bookings this week have the same intensity"
            }
        }
        return "booking sucessfull";
            }
        }
    }

    async getUsersBookings(userId){
        const [rows] = await pool.execute(
            'SELECT b.id AS bookingId, b.classID AS classId, c.className, c.classDate, b.bookedAt, '+
            'b.cancelled FROM bookings b inner join users u on b.userID= u.id inner join classes c on c.id=b.classID ' +
            'WHERE u.id=? ',[userId]
        );
        return rows;
    }

    async cancelBooking(bookingId,classId,userId){
        const [rows0] = await pool.execute(
            'select cancelled from bookings where id=? and cancelled=1' 
            ,[bookingId]
        );
        if(rows0.length>0)return"you can t cancel this, it is already cancelled";

        //set 1
        const [rows1] = await pool.execute(
            'Update bookings set cancelled=1 where id=?' 
            ,[bookingId]
        );
        //ia l pe primu de pe waiting list adauga book
        const [rows2] = await pool.execute(
            'Select * from waitlist WHERE classID = ? order by addedAt LIMIT 1',[classId]
        );

        if(rows2.length===0)return "booking canceled, noone on the waiting list";
        const waitlist = new Waitlist(rows2[0]);

        const [rows3] = await pool.execute(
            'DELETE FROM waitlist where id = ? ', [waitlist.id]
        );
        
        return "user left the waiting list:"+waitlist.userID+ await this.bookClass(waitlist.userID,classId);

    }

    async hasThreeOrMoreBookings(userId){
         const [rows] = await pool.execute(
            'select count(*) as count from bookings where userID=? and cancelled=0' 
            ,[userId]
        );
        if(rows[0].count>=3)return true;
        return false;
    }

    async hasAllBookingTheSame(userId){
         const [rows1] = await pool.execute(
            'select count(*) as count from bookings b inner join classes c on b.classID=c.id where userID=? and cancelled=0 and className like \'%Low\'' 
            ,[userId]
        );
        const [rows2] = await pool.execute(
            'select count(*) as count from bookings b inner join classes c on b.classID=c.id where userID=? and cancelled=0 and className like \'%High\'' 
            ,[userId]
        );
        if(rows1[0].count>=3 ||rows2[0].count>=3)return true;
        return false;
    }
}

module.exports = MainRepository;
