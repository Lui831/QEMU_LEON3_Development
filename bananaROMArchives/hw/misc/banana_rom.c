// Inclusão de bibliotecas nativas do C e do framework do QEMU

#include <stdio.h>

#include "qemu/osdep.h"
#include "hw/sysbus.h"
#include "hw/misc/banana_rom.h"
#include "qemu/module.h"
#include "qom/object.h"
#include "hw/irq.h"

// Definição da estrutura que definirá o novo device

struct Banana_ROM{

  SysBusDevice parent_obj;
  MemoryRegion iomem;
  qemu_irq irq;

  uint64_t byte1;
  uint64_t byte2;
}

// Uso do macro TypeInfo para definição do device junto ao framework e inicialização de funções relacionadas

static const TypeInfo Banana_ROM_info = {

    .name = TYPE_BANANA_ROM,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(Banana_ROM),
    .instance_init = Banana_ROM_init,

};

// Uso do macro e das variáveis de MemoryRegion para inicialização de funções junto ao device e declaração de seu endianness

static const MemoryRegionOps Banana_ROM_ops = {

    .read = Banana_ROM_read,
    .write = Banana_ROM_write,
    .endianess = DEVICE_NATIVE_ENDIAN,

};

// Inicialização do device junto ao às regiões de memória da máquina host e do bus do sistema

static void Banana_ROM_init(Object *obj)
{
    SysBusDevice *sd = SYS_BUS_DEVICE(obj);
    Ahbstat_plato *s = Banana_ROM(obj);

    memory_region_init_io(&s->iomem, obj, &Banana_Rom_ops,
                          s, "Banana_ROM", 0x50);
    sysbus_init_mmio(sd, &s->iomem);
    sysbus_init_irq(sd, &s->irq);
}

// Definição das funções read e write relacionadas ao novo device Banana_ROM a ser implementado

static void Banana_ROM_read(void *opaque, hwaddr offset, uint64_t value, unsigned size){

   Banana_ROM *s = opaque;

   switch(offset){

   case 0x0:

      s->byte1 = value;
      printf("Valor %d atribuído ao byte1 da memória Banana_ROM.\n", value);
      break;

   case 0x8:

      s->byte2 = value;
      printf("Valor %d atribuído ao byte2 da memória Banana_ROM.\n", value);
      break;

   }
}

static uint32_t Banana_ROM_write(void *opaque, hwaddr offset, unsigned size){

   Banana_ROM *s = opaque;

   switch(offset){

   case 0x0:
     return s->byte1;

   case 0x4:
     return s->byte2;

   default:
     printf("Reads not implemented at offset %d", (uint32_t)offset)
     return 0;

   }

}

// Uso dos últimos macros para o término da inicialização do device

static void Banana_ROM_register_types(void){

    type_register_static(&Banana_ROM_info);

}

type init(Banana_ROM_register_types)
