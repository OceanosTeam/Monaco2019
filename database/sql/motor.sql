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
  `energy` DECIMAL(4,2) DEFAULT '0',
  `Time` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `serverSideName` VARCHAR(15) DEFAULT 'motor',
  PRIMARY KEY (`id`)
);
