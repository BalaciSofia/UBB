function requireAuth(role) {
  return (req, res, next) => {
    if (!req.session.userId || !req.session.role) {
      return res.status(403).json({ success: false, message: 'Unauthorized' });
    }
    if (role && req.session.role !== role) {
      return res.status(403).json({ success: false, message: 'Unauthorized' });
    }
    next();
  };
}

module.exports = { requireAuth };
