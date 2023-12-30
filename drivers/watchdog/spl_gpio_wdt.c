#include <common.h>
#include <watchdog.h>
#include <asm/gpio.h>
#include <config.h>

#ifndef SPL_GPIO_WDT_PIN
#error "Please define SPL_GPIO_WDT_PIN for watchdog"
#endif

int init_wdt(void)
{
    int ret = 0;
    ret = gpio_request(SPL_GPIO_WDT_PIN, "wdt");
    if (ret)
        printf("Request for wdt gpio failed: %d\n", ret);

    return ret;
}

void watchdog_reset(void)
{
    static bool init = false;
    int ret;

    if(!init) {
        ret = init_wdt();
	if(ret)
	    return;
	init = true;
    }

    gpio_direction_output(SPL_GPIO_WDT_PIN, 0);
    gpio_set_value(SPL_GPIO_WDT_PIN, 1);
    return;
}
