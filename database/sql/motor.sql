-- ---------------------------
-- Table structure for motor
-- ---------------------------
CREATE TABLE IF NOT EXISTS `motor` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `Temperature` DECIMAL(6,2) DEFAULT '0',
  `VoltageIn` DECIMAL(6,2) DEFAULT '0',
  `RPM` INT DEFAULT '0',
  `PowerIn` DECIMAL(8,2) DEFAULT '0',
  `CurrentIn` DECIMAL(4,2) DEFAULT '0',
  `Time` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `serverSideName` VARCHAR(15) DEFAULT 'motor',
  PRIMARY KEY (`id`)
);

-- Test values
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('32', '35.22', '1500', '1200', '1');
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('33.2', '36.35', '1750', '1200', '1.2');
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('34.6', '38.27', '1700', '1200', '1.18');
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('32.3', '33.87', '1575', '1200', '1.1');
