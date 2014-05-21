/* linux/drivers/mtd/onenand/samsung_p1.h
 *
 * Partition Layout for Samsung Galaxy Tab (GSM variants)
 *
 */

struct mtd_partition s3c_partition_info[] = {

 /*This is partition layout from the oneNAND it SHOULD match the pitfile on the second page of the NAND.
   It will work if it doesn't but beware to write below the adress 0x01200000 there are the bootloaders.
   Currently we won't map them, but we should keep that in mind for later things like flashing bootloader
   from Linux. There is a partition 'efs' starting @ 0x00080000 40 256K pages long, it contains data for
   the modem like IMSI we don't touch it for now, but we need the data from it, we create a partition
   for that and copy the data from it. For this you need a image from it and mount it as vfat or copy
   it on a kernel with rfs support on the phone.

   Partitions on the lower NAND adresses:

   0x00000000 - 0x0003FFFF = first stage bootloader
   0x00040000 - 0x0007FFFF = PIT for second stage bootloader
   0x00080000 - 0x00A7FFFF = EFS: IMSI and NVRAM for the modem
   0x00A80000 - 0x00BBFFFF = second stage bootloader
   0x00BC0000 - 0x00CFFFFF = backup of the second stage bootloader (should be loaded if the other fails, unconfirmed!)
   0x00D00000 - 0x011FFFFF = PARAM.lfs config the bootloader

   #########################################################################################
   #########################################################################################
   ###### NEVER TOUCH THE FIRST 2 256k PAGES! THEY CONTAIN THE FIRST STAGE BOOTLOADER ######
   #########################################################################################
   #########################################################################################*/

        {
		.name		= "boot",
		.offset		= (72*SZ_256K),
		.size		= (30*SZ_256K), //101
	},
	{
		.name		= "recovery",
		.offset		= (102*SZ_256K),
		.size		= (30*SZ_256K), //131
	},
	{
		.name		= "system",
		.offset		= (132*SZ_256K),
		.size		= (1734*SZ_256K), //1865
	},
	{
		.name		= "radio",
		.offset		= (1866*SZ_256K),
		.size		= (88*SZ_256K), //1953
	},
	{
		.name		= "efs",
		.offset		= (1954*SZ_256K),
		.size		= (50*SZ_256K), //2003
	},
	{       /* The reservoir area is used by Samsung's Block Management Layer (BML)
	           to map good blocks from this reservoir to bad blocks in user
	           partitions. A special tool (bml_over_mtd) is needed to write
	           partition images using bad block mapping.
	           Currently, this is required for flashing the "boot" partition,
	           as Samsung's stock bootloader expects BML partitions.*/
		.name		= "reservoir",
		.offset		= (2004*SZ_256K),
		.size		= (44*SZ_256K), //2047
	},



		/* param.lfs partition is used to config the bootloader.
		   Params: SERIAL_SPEED, LCD_LEVEL, BOOT_DELAY, LOAD_RAMDISK, SWITCH_SEL, PHONE_DEBUG_ON,
		   LCD_DIM_LEVEL, LCD_DIM_TIME, MELODY_MODE, REBOOT_MODE, NATION_SEL, LANGUAGE_SEL,
		   SET_DEFAULT_PARAM, VERSION_LINE, COMMAND_LINE, BOOT_VERSION
		*/
/*
	{
		.name		= "param",
		.offset		= (52*SZ_256K),
		.size		= (20*SZ_256K), //71
	},
*/
};
