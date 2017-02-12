<?php

/**
 * @return mixed
 * uses form API to create settings form for Sugarbridge
 */

function sugarcrm_bridge_form(){

    $form['sugar_url'] = array(
        '#type' => 'textfield',
        '#title' => 'SugarCRM PROD URL',
        '#required' => false,
        '#default_value' => variable_get('sugar_url', ''),
        '#description' => t('This is the full rest endpoint url with trailing slash. Should end with something similar to \'rest/v10/\''),
        '#prefix' => t('<div style="padding: 6px 15px;background-color: #EEE;border:1px solid #C5C5C5;"><h5>NOTE: Prod and test URLS Are only detected on Sagoku sites.
                        On non Sagoku sites, enter the same URL in the TEST URL and PROD URL fields </h5>')
    );
    //padding:0 15px;background-color: #EEE;border:1px solid #C5C5C5;

    $form['sugar_test_url'] = array(
        '#type' => 'textfield',
        '#title' => 'SugarCRM TEST URL',
        '#required' => false,
        '#default_value' => variable_get('sugar_test_url', ''),
        '#description' => t('This is the full rest endpoint url with trailing slash. Should end with something similar to \'rest/v10/\''),
        '#suffix' => '</div>'
    );

    $form['sugar_port'] = array(
        '#type' => 'textfield',
        '#title' => 'SugarCRM Port',
        '#required' => false,
        '#default_value' => variable_get('sugar_port', ''),
    );

    $form['sugar_username'] = array(
        '#type' => 'textfield',
        '#title' => 'SugarCRM Username',
        '#required' => false,
        '#default_value' => variable_get('sugar_username', ''),
    );

    $form['sugar_password'] = array(
        '#type' => 'textfield',
        '#title' => 'SugarCRM Password',
        '#required' => false,
        '#default_value' => variable_get('sugar_password', ''),
    );

    $active = array(0 => t('Disabled'), 1 => t('Active'));

    $form['acton_queue_active'] = array(
        '#type' => 'radios',
        '#title' => t('Acton API Submit Queue'),
        '#default_value' => variable_get('acton_queue_active', '0'),
        '#options' => $active,
        '#description' => t('When enabled, acton api calls will be stored in the database and submitted over time to preserve API limits'),
    );

    $form['decouple_submissions'] = array(
        '#title' => 'Submission Processing',
        '#type' => 'select',
        '#options' => array(0 => 'Sugar submission occurs when form is submitted', 1 => 'Sugar submission is decoupled from form submission'),
        '#default_value' => variable_get('decouple_submissions', 0),
    );

    $form['queued_submissions'] = array(
        '#markup' => '<h3>' . l('See Sugar Submission Queue','admin/sugar-submissions') . '</h3>',
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#weight' => 80
    );
    $form['submit']['#validate'][] = 'is_valid_sugar_credentials';

    return $form;
}

function sugarcrm_bridge_form_submit($form, &$form_state) {


    $sugar_url      = $form_state['values']['sugar_url'];
    $sugar_test_url      = $form_state['values']['sugar_test_url'];
    $sugar_port     = $form_state['values']['sugar_port'];
    $sugar_username = $form_state['values']['sugar_username'];
    $sugar_password = $form_state['values']['sugar_password'];
    $acton_queue_active = $form_state['values']['acton_queue_active'];
    $decouple_submissions = $form_state['values']['decouple_submissions'];


    variable_set('sugar_url', $sugar_url);
    variable_set('sugar_test_url', $sugar_test_url);
    variable_set('sugar_port', $sugar_port);
    variable_set('sugar_username', $sugar_username);
    variable_set('sugar_password', $sugar_password);
    variable_set('acton_queue_active', $acton_queue_active);
    variable_set('decouple_submissions', $decouple_submissions);


        drupal_set_message(t('Variables have been saved'));

}

function is_valid_sugar_credentials(&$form, &$form_state){

    $sugar_url      = $form_state['values']['sugar_url'];
    $url      = $form_state['values']['sugar_test_url'];
    $port     = $form_state['values']['sugar_port'];
    $username = $form_state['values']['sugar_username'];
    $password = $form_state['values']['sugar_password'];

    if(isset($_SERVER['SGK_ENVIRONMENT']) &&  $_SERVER['SGK_ENVIRONMENT'] == 'prod'){
        $url = $sugar_url;
    }

    require_once libraries_get_path('sugarcrm7-api-wrapper-class') . '/vendor/autoload.php';

    $sugar = new \Spinegar\Sugar7Wrapper\Rest();
    try{
        $sugar->setUrl($url)
          ->setUsername($username)
          ->setPassword($password)
          ->connect();
    }catch(Exception $e){
        form_error($form, 'Connection to Sugar not possible with these values.  Error: ' . $e->getMessage());

    }

}

