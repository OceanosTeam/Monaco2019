-- ---------------------------
-- Table structure for motor
-- ---------------------------
CREATE TABLE IF NOT EXISTS `motor` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `speed` INT DEFAULT '0',
  `throttle` INT DEFAULT '0',
  `current` DECIMAL(4,2) DEFAULT '0',
  `voltage` DECIMAL(6,2) DEFAULT '0',
  `contrTemp` DECIMAL(6,2) DEFAULT '0',
  `motorTemp` DECIMAL(6,2) DEFAULT '0',
  `motErrCode` VARCHAR(8) DEFAULT '0',
  `cntrStat` VARCHAR(8) DEFAULT '0',
  `swStat` VARCHAR(8) DEFAULT '0',
  `Time` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `serverSideName` VARCHAR(15) DEFAULT 'motor',
  PRIMARY KEY (`id`)
);

-- Test values
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('32', '35.22', '1500', '1200', '1');
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('33.2', '36.35', '1750', '1200', '1.2');
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('34.6', '38.27', '1700', '1200', '1.18');
INSERT INTO `motor` (Temperature, VoltageIn, RPM, PowerIn, CurrentIn) VALUES ('32.3', '33.87', '1575', '1200', '1.1');
