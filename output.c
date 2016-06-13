#include <hdf5.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE "h5ex.h5"
#define DATASET "DS1"
#define DIM0 32

int write_data_hdf5(void) {
    hid_t file_id, dspace_id, dset_id;
    hsize_t dims[1];
    herr_t status;

    int i;
    double data[DIM0];

    /*
     * Create a new file using the default properties.
     */
    file_id = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Create dataspace.  Setting maximum size to NULL sets the maximum
     * size to be the current size.
     */
    dims[0] = DIM0;
    dspace_id = H5Screate_simple(1, dims, NULL);

    /*
     * Create the dataset.
     */
    dset_id = H5Dcreate(file_id, DATASET, H5T_IEEE_F64LE, dspace_id,
                        H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Make the data.
     */
    for (i = 0; i <= DIM0; i++) {
        data[i] = sin(2.0 * M_PI * i / DIM0);
    };

    /*
     * Write the data to the dataset.
     */
    status = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT,
                      data);

    /*
     * Close and release resources.
     */
    status = H5Dclose(dset_id);
    status = H5Sclose(dspace_id);
    status = H5Fclose(file_id);
    return 0;
}
