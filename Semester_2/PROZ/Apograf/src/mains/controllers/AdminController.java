
package mains.controllers;

import mains.Model;

/**
 * Class starting after logging in, when a person logging is an admin. Class inherits from PersonController.
 * @see PersonController
 * Class is not public, because we want only {@link Controller} to access this class.
 */

class AdminController  extends PersonController {
    /**
     * Class constructor, copying values to class parameters.
     * @param controller Parameter of type {@link Controller}.
     * @param mod Parameter of type {@link Model}.
     */
    public AdminController(Controller controller, Model mod){
        super(controller, mod);
    }
}
