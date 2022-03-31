-- ---------------------------
-- Table structure for gps
-- ---------------------------
CREATE TABLE IF NOT EXISTS `gps` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `Latitude` DECIMAL(8,6) DEFAULT '0',
  `Longitude` DECIMAL(8,6) DEFAULT '0',
  `Speed` DECIMAL(4,2) DEFAULT '0',
  `Time` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  `serverSideName` VARCHAR(15) DEFAULT 'gps',
  PRIMARY KEY (`id`)
);
