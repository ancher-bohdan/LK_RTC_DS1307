
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>

static int ds1307_custom_remove(struct i2c_client *client)
{
  return 0;
}

static int ds1307_custom_probe(struct i2c_client *client,
                                const struct i2c_device_id *id)
{
  int ret = 0;
  u8 stats_reg = 0;
  u8 reg = 0x07;

  struct i2c_msg msg[2] = {
    {
      .addr = client->addr,
      .len = 1,
      .buf = &reg,
    },
    {
      .addr = client->addr,
      .len = 1,
      .flags = I2C_M_RD,
      .buf = &stats_reg,
    }
  };

  ret = i2c_transfer(client->adapter, msg, 2);
  if(ret < 0)
  {
    pr_err("**************error in i2c transfering\n");
  }

  pr_info("status regiser: %d\n", stats_reg);

  reg = 0;
  ret = i2c_transfer(client->adapter, msg, 2);
  if(ret < 0)
  {
    pr_err("**************error in i2c transfering\n");
  }

  pr_info("sec: %d%d\n", (stats_reg >> 4) & 0x07, stats_reg & 0x0f);

  reg = 1;
  ret = i2c_transfer(client->adapter, msg, 2);
  if(ret < 0)
  {
    pr_err("**************error in i2c transfering\n");
  }

  pr_info("min: %d%d\n", stats_reg >> 4, stats_reg & 0x0f);

  reg = 2;
  ret = i2c_transfer(client->adapter, msg, 2);
  if(ret < 0)
  {
    pr_err("**************error in i2c transfering\n");
  }

  pr_info("hour: %d\n", stats_reg & 0x0f);

  return 0;
}

static const struct i2c_device_id ds1307_custom_id[] = {
  {"ds1307_custom"},
  { },
};

static const struct of_device_id ds1307_of_match[] = {
  {.compatible = "dallas,ds1307custom"},
  { }
};

static struct i2c_driver ds1307_custom_driver = {
  .driver = {
    .name = "rtc-ds1307-custom",
    .of_match_table = of_match_ptr(ds1307_of_match),
  },
  .probe = ds1307_custom_probe,
  .remove = ds1307_custom_remove,
  .id_table = ds1307_custom_id,
};

module_i2c_driver(ds1307_custom_driver);

MODULE_DESCRIPTION("RTC driver for DS1307 and similar chips");
MODULE_LICENSE("GPL");
