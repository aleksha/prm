# Create initial particles

## Scattering particles

They are created using `create.py`.
Assuming that it will be run in `output/` directory

```bash
conda activate pres-mc
ostap -b create.py
```

## Beam noise

Preserve beam frequency defined in `global_config.py`.

```bash
conda activate pres-mc
ostap -b create_beam.py
```

Also to run in `output/`.
