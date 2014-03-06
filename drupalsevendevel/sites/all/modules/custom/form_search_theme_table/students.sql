
-- ----------------------------
-- Table structure for `students`
-- ----------------------------
DROP TABLE IF EXISTS `students`;
CREATE TABLE `students` (
  `sid` int(11) NOT NULL AUTO_INCREMENT,
  `sname` varchar(255) DEFAULT NULL,
  `gender` char(1) DEFAULT NULL,
  PRIMARY KEY (`sid`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of students
-- ----------------------------
INSERT INTO `students` VALUES ('1', 'Anitha', 'f');
INSERT INTO `students` VALUES ('2', 'Swathi', 'f');
INSERT INTO `students` VALUES ('3', 'Suchitra', 'f');
INSERT INTO `students` VALUES ('4', 'Ramya', 'f');
INSERT INTO `students` VALUES ('5', 'Swapna', 'f');
INSERT INTO `students` VALUES ('6', 'Naveena', 'f');
INSERT INTO `students` VALUES ('7', 'Ajay', 'm');
INSERT INTO `students` VALUES ('8', 'Raj', 'm');
INSERT INTO `students` VALUES ('9', 'David', 'm');
INSERT INTO `students` VALUES ('10', 'Gopi', 'm');
INSERT INTO `students` VALUES ('11', 'Ramu', 'm');
INSERT INTO `students` VALUES ('12', 'Shyam', 'm');
